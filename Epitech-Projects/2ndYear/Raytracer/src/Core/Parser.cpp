/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** Parser
*/

#include "Parser.hpp"

RayTracer::Parser::Parser()
{
}

RayTracer::Parser::~Parser()
{
}

int RayTracer::Parser::parse(const int ac, const char** av)
{
    if (ac < 2) {
        std::cerr << "Usage: " << av[0] << " <scene_file>" << std::endl;
        throw Error("Invalid number of arguments");
    }
    _filepath = av[1];
    try {
        cfg.readFile(_filepath.c_str());
    } catch (const libconfig::ParseException &e) {
        std::cerr << "Parse error at "
              << e.getFile() << ":"
              << e.getLine() << " - "
              << e.getError() << std::endl;
    }
    return 0;
}

std::unique_ptr<RayTracer::FileHandler>
    RayTracer::Parser::parseFileHandler()
{
    std::string filePath = _filepath.substr(0, _filepath.find_last_of('.')) + ".ppm";

    return std::make_unique<RayTracer::FileHandler>(filePath);
}

std::vector<std::unique_ptr<RayTracer::ILight>>
    RayTracer::Parser::parseLights(){
    std::vector<std::unique_ptr<RayTracer::ILight>> lights;

    if (!cfg.getRoot().exists("lights"))
        return lights;

    const libconfig::Setting& s = cfg.getRoot()["lights"];

    double ambient   = s.exists("ambient")   ? (double)s["ambient"]   : 0.3;
    double diffuse   = s.exists("diffuse")   ? (double)s["diffuse"]   : 0.8;
    double intensity = s.exists("intensity") ? (double)s["intensity"] : 1.0;

    if (s.exists("directional")) {
        for (auto& l : s["directional"]) {
            DirectionalBuilder builder;

            lights.push_back(
                builder.setColor((int)l["color"]["r"], (int)l["color"]["g"], (int)l["color"]["b"])
                    .setAmbient(ambient)
                    .setDiffuse(diffuse)
                    .setIntensity(intensity)
                    .setDirection((double)l["direction"]["x"], (double)l["direction"]["y"], (double)l["direction"]["z"])
                    .build()
            );
        }
    }

    if (s.exists("point")) {
        for (auto& l : s["point"]) {
            PointBuilder builder;

            lights.push_back(
                builder.setColor((int)l["color"]["r"], (int)l["color"]["g"], (int)l["color"]["b"])
                    .setAmbient(ambient)
                    .setDiffuse(diffuse)
                    .setIntensity(intensity)
                    .setOrigin((double)l["origin"]["x"], (double)l["origin"]["y"], (double)l["origin"]["z"])
                    .build()
            );
        }
    }

    return lights;
}

std::unique_ptr<RayTracer::Material> RayTracer::Parser::parseMaterial(libconfig::Setting &s){
    MaterialBuilder builder;

    if (s.exists("color"))
        builder.setColor(RayTracer::Color(
            (int)s["color"]["r"],
            (int)s["color"]["g"],
            (int)s["color"]["b"]
        ));
    if (s.exists("reflectivity"))
        builder.setReflectivity((double)s["reflectivity"]);
    if (s.exists("transparency"))
        builder.setTransparency((double)s["transparency"]);
    if (s.exists("refractivity"))
        builder.setRefractivity((double)s["refractivity"]);

    return builder.build();
}   

std::vector<std::unique_ptr<RayTracer::IPrimitive>> 
    RayTracer::Parser::parseShapes(){
    std::vector<std::unique_ptr<RayTracer::IPrimitive>> shapes;

    if (!cfg.getRoot().exists("primitives"))
        return shapes;

    const libconfig::Setting& s = cfg.getRoot()["primitives"];

    if (s.exists("planes")) {
        for (auto &primitive : s["planes"]) {
            PlaneBuilder builder;

            shapes.push_back(
                builder.setMaterial(parseMaterial(primitive["material"]))
                .setAxis(primitive["axis"].c_str())
                .setPosition((double)primitive["position"])
                .build()
            );
        }
    }

    if (s.exists("spheres")) {
        for (auto &primitive : s["spheres"]) {
            SphereBuilder builder;

            shapes.push_back(
                builder.setMaterial(parseMaterial(primitive["material"]))
                .setRadius(primitive["r"])
                .setOrigin({primitive["origin"]["x"], primitive["origin"]["y"], primitive["origin"]["z"]})
                .build()
            );
        }
    }

    if (s.exists("cones")) {
        for (auto &primitive : s["cones"]) {
            ConeBuilder builder;

            shapes.push_back(
                builder.setMaterial(parseMaterial(primitive["material"]))
                    .setRadius(primitive["r"])
                    .setOrigin({primitive["origin"]["x"], primitive["origin"]["y"], primitive["origin"]["z"]})
                    .setHeight(primitive["height"])
                    .setRotation({primitive["rotation"]["x"], primitive["rotation"]["y"], primitive["rotation"]["z"]})
                    .setScale({primitive["scale"]["x"], primitive["scale"]["y"], primitive["scale"]["z"]})
                    .build()
            );
        }
    }

    if (s.exists("cylinders")) {
        for (auto &primitive : s["cylinders"]) {
            CylinderBuilder builder;

            shapes.push_back(
                builder.setMaterial(parseMaterial(primitive["material"]))
                    .setRadius(primitive["r"])
                    .setOrigin({primitive["origin"]["x"], primitive["origin"]["y"], primitive["origin"]["z"]})
                    .setHeight(primitive["height"])
                    .setRotation({primitive["rotation"]["x"], primitive["rotation"]["y"], primitive["rotation"]["z"]})
                    .setScale({primitive["scale"]["x"], primitive["scale"]["y"], primitive["scale"]["z"]})
                    .build()
            );
        }
    }

    return shapes;
}

std::unique_ptr<RayTracer::Camera>
    RayTracer::Parser::parseCamera() {
    CameraBuilder builder;

    try
    {
        const libconfig::Setting& s = cfg.getRoot()["camera"];

        return builder.setOrigin((double)s["origin"]["x"], (double)s["origin"]["y"], (double)s["origin"]["z"])
            .setResolution((double)s["resolution"]["width"], (double)s["resolution"]["height"])
            .setFov((double)s["fov"])
            .setBgColor((int)s["bgColor"]["r"], (int)s["bgColor"]["g"], (int)s["bgColor"]["b"])
            .build();
    }
    catch(const libconfig::ConfigException& e)
    {
        throw Error(std::string("Error parsing camera: ") + e.what());
    }
}
