//
// Created by part4 on 22.03.2024.
//

#ifndef NGRAMSUTIL_H
#define NGRAMSUTIL_H

#include "Libraries.h"
#include "FileService.h"

namespace utils {
    class NgramsUtil {
        std::map<const std::string , int> counter_;
        std::int64_t total_ = 0;
        int mode_;
    public:
        explicit NgramsUtil() {
            this->mode_ = 1;
            this->counter_ = std::map<const std::string, int>();
        };

        [[nodiscard]] const std::map<const std::string, int> &getCounter() const;

        [[nodiscard]] int64_t getTotal() const;

        void processLine(const std::string& line);

		void reset();

        ~NgramsUtil() = default;
    };
}

#endif //NGRAMSUTIL_H
