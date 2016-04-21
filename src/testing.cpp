// #include <patterns.h>
// #include <BouncingDot.h>
// #include <lmcp.h>

// char target[] = "10.42.3.12";

// // 20 jobs max for now.
// size_t num_patternjobs = 0;
// const size_t max_patternjobs = 20;
// Pattern patternjobs[max_patternjobs];

// void process_patternjobs()
// {
//     // // generate a new frame
//     // pattern.generate();
//     // // send it out on the coupled network.
//     // pattern.process();
//     for(int job = 0; job < num_patternjobs; job++)
//     {
//         Pattern pat = patternjobs[job];
//         pat.generate();
//         pat.process();

//         // wait some time
//         usleep(30e3);
//     }
// }

// void create_pattern_test()
// {
//     // size 96x48 at pos (0, 0) and size (96 * 48)
//     const int width = 96 / 2;
//     const int height = 48 / 2;
//     rect_t ledboard_dims = {0, 0, width, height};

//     BouncingDot testdot = BouncingDot(ledboard_dims);
//     Lmcp network = Lmcp(target);
//     // creates a pattern and gives it a name (GETNAME(pattern)) and associate a
//     // network com protocol with it.
//     Pattern testpattern = Pattern(testdot, network, GETNAME(BouncingDot));
//     // run it for a bit but still exit.
//     for(int i = 0; i < (width * height) / 2; i++)
//     {
//         testpattern.generate();
//         testpattern.process();
//         usleep(30e3);
//     }

// }

// void add_pattern(Surface &pat, Network &net, const char *name)
// {
//     // check if we are at our limit.
//     if(num_patternjobs >= max_patternjobs)
//         return;

//     patternjobs[num_patternjobs] = Pattern(pat, net, name);
//     num_patternjobs++;
// }

// void job_creation_test()
// {
//     //create a job

//     rect_t dims = {0, 0, 96, 48};
//     // this works as opposed to just letting the compiler make the object.
//     // if the compiler makes the object then it doesnt called the derived class
//     // it's base constructors.
//     Surface *pattern = new BouncingDot(dims);
//     Network *lmcp = new Lmcp(target);
    
//     add_pattern(*pattern, *lmcp, GETNAME(BouncingDot));

//     // run a few times
//     for(int i = 0; i < 2000; i++)
//     {
//         process_patternjobs();
//     }
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <unistd.h>
// #include <string.h>

// #include <iostream>

// #include <gflags/gflags.h>

// DEFINE_double(fps, 20.0, "set fps for program to run at.");

// void some_general_info()
// {
//     printf("Build with gcc version: %s.\n", __VERSION__);
//     printf("Compiled at: %s.\n", __TIMESTAMP__);
//     printf("\n");
// }

// // int main(int argc, char **argv)
// // {
// //     ::google::ParseCommandLineFlags(&argc, &argv, true);
// //     std::cout << "FLAGS_fps: " << FLAGS_fps << "\n";
// //     some_general_info();

// //     return 0;
// // }







    // if(config["patternjob"])
    // {
    //     YAML::Node patternjob = config["patternjob"].as<YAML::Node>();

    //     YAML::Node matrix = patternjob["matrix"].as<YAML::Node>();
    //     YAML::Node matrixsim = patternjob["matrixsim"].as<YAML::Node>();
    //     YAML::Node protocol = patternjob["protocol"].as<YAML::Node>();
    //     YAML::Node pattern = patternjob["pattern"].as<YAML::Node>();

    //     if(matrix)
    //     {
    //         matrix_dims.x = matrix["x"].as<int>();
    //         matrix_dims.y = matrix["y"].as<int>();
    //         matrix_dims.width = matrix["width"].as<int>();
    //         matrix_dims.height = matrix["height"].as<int>();
    //         printf("x: %d, y: %d, width: %d, height: %d\n",
    //                matrix_dims.x, matrix_dims.y,
    //                matrix_dims.width, matrix_dims.height);
    //     }
    //     else
    //     {
    //         printf("no valid matrix dimensions found in config file!.\n");
    //         return -1;
    //     }

    //     if(matrixsim)
    //     {
    //         int pixelsize = matrixsim["pixelsize"].as<int>();
    //         MatrixSimulator *asim = new MatrixSimulator(matrix_dims, pixelsize);
    //         sim = asim;
    //     }
    //     else
    //     {
    //         printf("no matrixsim found in config. running without.\n");
    //     }

    //     if(protocol)
    //     {
    //         if(protocol["type"].as<string>() == "lmcp")
    //         {
    //             char target[20];
    //             for(int i = 0; protocol["target"].as<string>()[i]; i++)
    //             {
    //                 target[i] = protocol["target"].as<string>()[i];
    //                 target[i+1] = 0;
    //             }
    //             int port = protocol["port"].as<int>();
    //             net = new Lmcp(target, port);
    //         }
    //         else
    //         {
    //             printf("no valid type set. going for Network()!.\n");
    //         }
    //     }
    //     else
    //     {
    //         printf("no protocol selected in config file meaning it goes no where!.\n");
    //     }

    //     if(pattern)
    //     {
    //         if(pattern["job"].as<string>() == "BouncingDot")
    //         {
    //             surf = new BouncingDot(matrix_dims);
    //         }
    //         else
    //         {
    //             printf("no know pattern selected in config!.\n");
    //             return -1;
    //         }
    //     }
    //     else
    //     {
    //         printf("no pattern selected in config file!.\n");
    //         return -1;
    //     }

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
    // }