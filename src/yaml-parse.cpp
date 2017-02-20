#include "yaml-parse.h"

int yaml_parse(const char *config_file)
{
    rect_t matrix_rect = {0, 0, 0, 0};
    MatrixSimulator *sim = NULL;
    Surface *surf = NULL;
    Network *net = NULL;

    YAML::Node config = YAML::LoadFile(config_file);
    if(config.size() == 0 || !(config))
    {
        fprintf(stderr,
                "config file incomplete or empyt!. exiting\n");
        return -1;
    }
    for(YAML::const_iterator j = config.begin();j != config.end(); ++j) {
        YAML::Node pattern_job = config[j->first.as<std::string>()];
        YAML::Node matrix = pattern_job["matrix"].as<YAML::Node>();
        YAML::Node matrixsim = pattern_job["matrixsim"].as<YAML::Node>();
        YAML::Node protocol = pattern_job["protocol"].as<YAML::Node>();
        YAML::Node pattern = pattern_job["pattern"].as<YAML::Node>();
        
        // a first test to see if pattern exist nothing else matters if it doesn't
        // exist.
        const char *pname;
        if(pattern)
        {
            pname = pattern["job"].as<std::string>().c_str();
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
                    pname,
                    j->first.as<std::string>().c_str());
            return -1;
        }

        if(matrixsim)
        {
            int pixelsize = matrixsim["pixelsize"].as<int>();
            sim = new MatrixSimulator(matrix_rect, pixelsize);
        }
        else
        {
            fprintf(stderr,
                    "%s: running pattern without simulator.\n"
                    "config-node: %s\n",
                    pname,
                    j->first.as<std::string>().c_str());
        }

        if(protocol)
        {
            const char *type = protocol["type"].as<std::string>().c_str();
            const char *target = protocol["target"].as<std::string>().c_str();
            int port = protocol["port"].as<int>();
            net = builder.protocol_builder(type, target, port);
            if(net == NULL)
            {
                fprintf(stderr,
                        "%s couldn't be created. not sending.\n",
                        type);
            }
        }
        else
        {
            fprintf(stderr,
                    "%s: no protocol found. not sending.\n"
                    "config-node: %s\n",
                    pname,
                    j->first.as<std::string>().c_str());
        }

        // after all this we are sure pattern exist.
        // because we did a test for that earlier.
        const char *name = pattern["job"].as<std::string>().c_str();
        surf = builder.surface_builder(name, matrix_rect);
        if(surf == NULL)
        {
            fprintf(stderr,
                    "%s couldn't be created. exiting. \n",
                    name);
            return -1;
        }
        std::shared_ptr<Pattern_t> pat = std::shared_ptr<Pattern_t>(new Pattern_t());
        pat->surf = surf;
        pat->sim = sim;
        pat->net = net;
        patternjobs.register_pattern(pat);
    }

    // so far so good! lets return 0 for that!
    return 0;
}
