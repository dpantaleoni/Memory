//  Random Integer Library
//  Copyright 2020 Matt Cervantes 
//  Licensed under the Educational Community License, Version 2.0 (the "License"); 
//  you may not use this file except in compliance with the License. You may
//  obtain a copy of the License at

//  https://opensource.org/licenses/ECL-2.0

// 	Unless required by applicable law or agreed to in writing,
//  software distributed under the License is distributed on an "AS IS"
// 	BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// 	or implied. See the License for the specific language governing
// 	permissions and limitations under the License.

#ifndef _RANDOM_INT_H_
#define _RANDOM_INT_H_

#if __cplusplus < 201103L
    #error RandomInt requires C++11 or newer.
#endif

#include <chrono>
#include <random>
#include <unordered_map>
#include <stdexcept>

namespace Random
{
    // Generates random integers within range 
    class RandomInt
    {
        private:

        int _low;
        int _diff;
        unsigned int _maxRepeats;
        static std::default_random_engine _rng;
        std::uniform_int_distribution<int> _dist;
        std::unordered_map<int, unsigned int> _generatedNumbers;
        
        public:

        RandomInt(int low, int high, unsigned int repeats = 0) : _low(low), _diff(high-low+1), _maxRepeats(repeats)
        {
            if (low >= high)
                throw std::runtime_error("RandomInt: Error - low value must be less than high value");
            
            if (_maxRepeats != 0)
            {
                for (int i = low; i <= high; ++i)
                {
                    _generatedNumbers[i] = 0;
                }
            }

            _dist = std::uniform_int_distribution<>{low, high};
        }

        int get()
        {
            int returnVal = _dist(_rng);

            if (_maxRepeats == 0)
                return returnVal;

            std::uniform_int_distribution<int> trueOrFalseDist{0,1};
            bool increment = trueOrFalseDist(_rng);

            int endPoint;
            if (increment)
            {
                endPoint = returnVal-1;
                if (endPoint < _low)
                    endPoint = _low+_diff-1;
            }
            else
            {
                endPoint = returnVal+1;
                if (endPoint > _low+_diff-1)
                    endPoint = _low;
            }

            while (_generatedNumbers[returnVal] == _maxRepeats)
            {
                if (increment)
                {
                    if (++returnVal > (_low+_diff-1))
                        returnVal = _low;
                }
                else
                {
                    if (--returnVal < _low)
                        returnVal = _low+_diff-1;
                }

                if (returnVal == endPoint && _generatedNumbers[returnVal] == _maxRepeats)
                {
                    throw std::runtime_error("RandomInt: Error - All random numbers in the range have been generated to the max repeat value");
                }
            }

            _generatedNumbers[returnVal]++;

            return returnVal;
        }
    };

    std::default_random_engine RandomInt::_rng{static_cast<uint_fast32_t>(std::chrono::system_clock::now().time_since_epoch().count())};
}

#endif
