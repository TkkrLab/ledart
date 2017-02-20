#ifndef __YAML_PARSE_H__
#define __YAML_PARSE_H__

#include <graphics/surface.h>
#include <matrixsim.h>

#include <network/network.h>
#include <patterns/patterns.h>

#include <builder.h>

#include <yaml-cpp/yaml.h>
#include <memory>

extern PatternJobs patternjobs;
extern Builder builder;

int yaml_parse(std::string);

#endif
