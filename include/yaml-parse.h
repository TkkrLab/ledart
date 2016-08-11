#ifndef __YAML_PARSE_H__
#define __YAML_PARSE_H__

#include <graphics/surface.h>
#include <matrixsim.h>
#include <network/network.h>
#include <yaml-cpp/yaml.h>
#include <builder.h>
#include <patterns/patterns.h>

extern PatternJobs patternjobs;
extern Builder builder;

int yaml_parse(const char *);

#endif