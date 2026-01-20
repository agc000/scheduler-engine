#ifndef IO_H
#define IO_H

#include "models.h"
#include <string>
#include <vector>

namespace io {


    std::vector<Task> read_tasks_from_csv(const std::string& filepath);

   //Helper Func
    std::string trim(const std::string& str);

  //Helper Func
    std::vector<std::string> split(const std::string& str, char delimiter);

}

#endif
