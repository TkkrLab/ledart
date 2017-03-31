#include "argparse.h"

using namespace google;

extern PatternJobs patternjobs;
extern Builder builder;

DEFINE_bool(debug, false, "enable debug logging.");
DEFINE_double(fps, 0, "Set Fps for program.");
DEFINE_bool(showFps, false, "enable fps printing.");
DEFINE_bool(n, false, "run program once.");
DEFINE_string(config_file, "test.yml", "run with selected config_file.");

int parse_yaml(std::string config_file)
{
    rect_t matrix_rect = {0, 0, 0, 0};

    simulator_ptr sim = NULL;
    surface_ptr surf = NULL;
    output_ptr out = NULL;

    YAML::Node config = YAML::LoadFile(config_file);
    if(config.size() == 0 || !(config))
    {
        fprintf(stderr,
                "config file incomplete or empty!. exiting\n");
        return -1;
    }
    for(YAML::const_iterator j = config.begin();j != config.end(); ++j) {
        YAML::Node pattern_node = config[j->first.as<std::string>()];
        YAML::Node matrix = pattern_node["matrix"].as<YAML::Node>();
        YAML::Node matrixsim = pattern_node["matrixsim"].as<YAML::Node>();
        YAML::Node protocol = pattern_node["protocol"].as<YAML::Node>();
        YAML::Node pattern = pattern_node["pattern"].as<YAML::Node>();
        
        // a first test to see if pattern exist nothing else matters if it doesn't
        // exist.
        std::string pname;
        if(pattern)
        {
            pname = pattern["job"].as<std::string>();
        }
        else
        {
            fprintf(stderr,
                    "exiting because no pattern exist/selected. \n"
                    "config-node: %s\n",
                    j->first.as<std::string>().c_str());
            return -1;
        }

        if(matrix)
        {
            matrix_rect.x = matrix["x"].as<int>();
            matrix_rect.y = matrix["y"].as<int>();
            matrix_rect.width = matrix["width"].as<int>();
            matrix_rect.height = matrix["height"].as<int>();
        }
        else
        {
            fprintf(stderr,
                    "%s: no valid dimensions found. exiting.\n"
                    "config-node: %s\n",
                    pname.c_str(),
                    j->first.as<std::string>().c_str());
            return -1;
        }

        if(matrixsim)
        {
            int pixelsize = matrixsim["pixelsize"].as<int>();
            bool fullscreen = false;
            if(matrixsim["fullscreen"])
                fullscreen = matrixsim["fullscreen"].as<bool>();
            /* there is a small leak here, probably due to SDL */
            sim = simulator_ptr(new MatrixSimulator(matrix_rect, pixelsize, fullscreen));
        }
        else
        {
            fprintf(stderr,
                    "%s: running pattern without simulator.\n"
                    "config-node: %s\n",
                    pname.c_str(),
                    j->first.as<std::string>().c_str());
        }

        if(protocol)
        {
            std::string type = protocol["type"].as<std::string>();
            out = builder.protocol_builder(type, protocol);
            if(out == NULL)
            {
                fprintf(stderr,
                        "%s couldn't be created. not sending.\n",
                        type.c_str());
            }
        }
        else
        {
            fprintf(stderr,
                    "%s: no protocol found. not sending.\n"
                    "config-node: %s\n",
                    pname.c_str(),
                    j->first.as<std::string>().c_str());
        }

        // after all this we are sure pattern exist.
        // because we did a test for that earlier.
        std::string name = pattern["job"].as<std::string>().c_str();
        surf = builder.surface_builder(name, matrix_rect, pattern);
        if(surf == NULL)
        {
            fprintf(stderr,
                    "%s couldn't be created. exiting. \n",
                    name.c_str());
            return -1;
        }
        pattern_ptr pat = pattern_ptr(new Pattern_t());
        pat->surf = std::move(surf);
        pat->sim = std::move(sim);
        pat->out = std::move(out);
        patternjobs.register_pattern(pat);
    }

    // so far so good! lets return 0 for that!
    return 0;
}

options_t arg_parse(int argc, char** argv)
{
    options_t options;
    SetUsageMessage("Usage: ");

    ParseCommandLineFlags(&argc, &argv, true);
    options.debug = FLAGS_debug;
    options.fps = 1 / (FLAGS_fps / 1000);
    options.run_once = FLAGS_n;
    options.showFps = FLAGS_showFps;
    options.config_file += std::string(FLAGS_config_file);
    return options;
}
