#ifndef __ARGPARSE_H__
#define __ARGPARSE_H__

/*
    this file contains functions for parsing commandline params,
    and for parsing config files.
*/

#include <yaml-cpp/yaml.h>
#include <gflags/gflags.h>

#include <eventhandler.h>
#include <patterns/patterns.h>

#include <string>
#include <builder.h>
#include <matrixsim.h>
#include <network/network.h>
#include <graphics/surface.h>

typedef struct {
    double fps = 0;
    bool showFps = false;
    bool run_once = false;
    bool list = false;
    bool debug = false;
    // serves as prefix.
    std::string config_file = "configs/";
} options_t;

extern PatternJobs patternjobs;
extern Builder builder;

int parse_yaml(std::string);
options_t arg_parse(int, char**);

#endif
