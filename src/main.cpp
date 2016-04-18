#include <iostream>
#include <stdio.h>

using namespace std;

extern "C"
{
    #include <SDL2/SDL.h>
}

#include <lmcp.h>
#include <BouncingDot.h>
#include <eventhandler.h>
#include <patterns.h>

#include <yaml-cpp/yaml.h>

// these are global so that other patterns could use them if they want.
// via the extern keyword.
EventHandler global_event_handler = EventHandler();
PatternJobs patternjobs = PatternJobs();

// called when keyboard intterup comes
void ki_func(int sig)
{
    printf("\nCaught keyboard interrupt.! signal: %d\n", sig);
    exit(1);
}

Surface *surface_builder(char *name, rect_t dims)
{
    if(strcmp(GETNAME(BouncingDot), name))
    {
        Surface *surf = new BouncingDot(dims);
    }
}

int main(int argc, char **argv)
{
    MatrixSimulator *sim = NULL;
    Surface *surf = NULL;
    Network *net = NULL;

    rect_t matrix_dims = {0, 0, 0, 0};

    signal(SIGINT, ki_func);

    YAML::Node config = YAML::LoadFile("configs/test.yml");

    if(config["patternjob"])
    {
        YAML::Node patternjob = config["patternjob"].as<YAML::Node>();

        YAML::Node matrix = patternjob["matrix"].as<YAML::Node>();
        YAML::Node matrixsim = patternjob["matrixsim"].as<YAML::Node>();
        YAML::Node protocol = patternjob["protocol"].as<YAML::Node>();
        YAML::Node pattern = patternjob["pattern"].as<YAML::Node>();

        if(matrix)
        {
            matrix_dims.x = matrix["x"].as<int>();
            matrix_dims.y = matrix["y"].as<int>();
            matrix_dims.width = matrix["width"].as<int>();
            matrix_dims.height = matrix["height"].as<int>();
            printf("x: %d, y: %d, width: %d, height: %d\n",
                   matrix_dims.x, matrix_dims.y,
                   matrix_dims.width, matrix_dims.height);
        }
        else
        {
            printf("no valid matrix dimensions found in config file!.\n");
            return -1;
        }

        if(matrixsim)
        {
            int pixelsize = matrixsim["pixelsize"].as<int>();
            sim = new MatrixSimulator(matrix_dims, pixelsize);
        }
        else
        {
            printf("no matrixsim found in config. running without.\n");
        }

        if(protocol)
        {
            if(protocol["type"].as<string>() == "lmcp")
            {
                char target[20];
                for(int i = 0; protocol["target"].as<string>()[i]; i++)
                {
                    target[i] = protocol["target"].as<string>()[i];
                    target[i+1] = 0;
                }
                int port = protocol["port"].as<int>();
                net = new Lmcp(target, port);
            }
            else
            {
                printf("no valid type set. going for Network()!.\n");
            }
        }
        else
        {
            printf("no protocol selected in config file meaning it goes no where!.\n");
        }

        if(pattern)
        {
            if(pattern["job"].as<string>() == "BouncingDot")
            {
                surf = new BouncingDot(matrix_dims);
            }
            else
            {
                printf("no know pattern selected in config!.\n");
                return -1;
            }
        }
        else
        {
            printf("no pattern selected in config file!.\n");
            return -1;
        }

        // std::cout << "patternjob: \n";
        // YAML::Node patternjob = config["patternjob"].as<YAML::Node>();
        // std::cout << patternjob << "\n";
        // YAML::Node pattern = patternjob["pattern"].as<YAML::Node>();
        // std::cout << pattern << "\n";
        // YAML::Node job = pattern["job"].as<YAML::Node>();
        // std::cout << job << "\n\n";

        // YAML::Node protocol = patternjob["protocol"].as<YAML::Node>();
        // std::cout << protocol << "\n";
        // int port = 42;
        // string target = "10.42.3.12";
        // string protocol_type = "Network";
        // if(protocol["port"])
        // {
        //     port = protocol["port"].as<int>();
        // }
        // if(protocol["target"])
        // {
        //     target = protocol["target"].as<string>();
        // }
        // std::cout << "target: " << target
        //           << "port: " << port << "\n";

        // for(size_t i = 0; i < config["pattern"].size(); i++)
        // {
        //     std::cout << config["pattern"][i] << "\n";
        // }
    }

    Pattern_t pat = {NULL, NULL, NULL};
    pat.surf = surf;
    pat.sim = sim;
    pat.net = net;
    patternjobs.register_pattern(&pat);

    for(;;)
    {
        global_event_handler.process();
        patternjobs.process();
        SDL_Delay(33.33);
    }
    return 0;
}