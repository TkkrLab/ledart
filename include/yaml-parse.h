#ifndef __YAML_PARSE_H__
#define __YAML_PARSE_H__

#include <surface.h>
#include <matrixsim.h>
#include <network.h>
#include <yaml-cpp/yaml.h>
#include <builder.h>
#include <patterns.h>

extern PatternJobs patternjobs;
extern Builder builder;

int yaml_parse();

#endif