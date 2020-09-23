#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "global.h"
#include "ray.h"
#include "camera.h"
#include "object\objectList.h"
#include "object\sphere.h"
#include "material\lambertian.h"
#include "material\matel.h"
#include "material\dielectric.h"

const int MAX_DEPTH = 50;

vec3 rayColor(const ray& r, const object& world, int depth){
    if(depth <= 0) return vec3(0, 0, 0);
    hitRecord rec;
    if(world.hit(r, 0.001, Infinity, rec)){
        vec3 attenuation;
        ray scattered;
        if(rec.mat->scatter(r, rec, attenuation, scattered)){
            return attenuation * rayColor(scattered, world, depth - 1);
        }
        return vec3(0, 0, 0);
    }
    vec3 dir = normalize(r.getDir());
    float t = 0.5 * (dir.getY() + 1);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

objectList randomScene(){
    objectList world;
    
    world.add(make_shared<sphere>(vec3(0, -1000, 0), 1000, make_shared<lambertian>(vec3(0.5, 0.5, 0.5))));

    int i = 1;
    for(int a = -11; a < 11; ++a){
        for(int b = -11; b < 11; ++b){
            auto chooseMat = randomFloat();
            vec3 center(a + 0.9*randomFloat(), 0.2, b + 0.9*randomFloat());
            if((center - vec3(4, 0.2, 0)).length() > 0.9){
                if(chooseMat < 0.65){
                    auto albedo = vec3::random() * vec3::random();
                    world.add(make_shared<sphere>(center, 0.2, make_shared<lambertian>(albedo)));
                }
                else if(chooseMat < 0.9){
                    auto albedo = vec3::random(0.5, 1);
                    auto fuzz = randomFloat(0, 0.4);
                    world.add(make_shared<sphere>(center, 0.2, make_shared<matel>(albedo, fuzz)));
                }
                else{
                    world.add(make_shared<sphere>(center, 0.2, make_shared<dielectric>(1.5)));
                }
            }
        }
    }
    world.add(make_shared<sphere>(vec3(0, 1.0, 0), 1.0, make_shared<dielectric>(1.5)));
    world.add(make_shared<sphere>(vec3(-4, 1.0, 0), 1.0, make_shared<lambertian>(vec3(0.6, 0.1, 0.7))));
    world.add(make_shared<sphere>(vec3(3, 1.0, -0.5), 1.0, make_shared<matel>(vec3(0.7, 0.6, 0.5), 0)));

    return world;
}

int main()
{
    const int imgWidth = 800;
    const int imgHeight = 600;
    const int samplerPerPixel = 50;
    const double scale = double(imgWidth)/imgHeight;
    const vec3 worldUp(0, 1.0, 0);
    vec3 cameraPos(4, 2, 16);
    vec3 cameraTarget(0, 1.0, 0);
    float focusDistance = 10.0;
    float aperture = 0.1;

    unsigned char data[imgWidth * imgHeight * 4] = {0};

    camera cam(cameraPos, cameraTarget, worldUp, 20, scale, aperture, focusDistance);

    objectList world = randomScene();

    for(int j = imgHeight - 1; j >= 0; --j){
        for(int i = 0; i < imgWidth ; ++i){
            vec3 color(0, 0, 0);
            for(int k = 0; k < samplerPerPixel; ++k){
                float u = (i + randomFloat())/imgWidth;
                float v = (j + randomFloat())/imgHeight;
                ray r = cam.getRay(u, v);
                color += rayColor(r, world, MAX_DEPTH);
            }
            color = color / samplerPerPixel;
            data[4*(i + (imgHeight - 1 - j)*imgWidth)] = sqrt(color.getX()) * 255.999;
            data[4*(i + (imgHeight - 1 - j)*imgWidth)+1] = sqrt(color.getY()) * 255.999;
            data[4*(i + (imgHeight - 1 - j)*imgWidth)+2] = sqrt(color.getZ()) * 255.999;
            data[4*(i + (imgHeight - 1 - j)*imgWidth)+3] = 255;
        }
        system("cls");
        std::cout<<100 - (100*j)/imgHeight<<"%";
    }
    stbi_write_png("main.png", imgWidth, imgHeight, 4, data, imgWidth * 4);
    return 0;
}