/// @file test/libstd/memory.cpp
/// @data 06/06/2016 22:23:53
/// @author Ambroise Leclerc
/// @brief BDD tests for <memory>
//
// Copyright (c) 2016, Ambroise Leclerc
//   All rights reserved.
//
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions are met:
//
//   * Redistributions of source code must retain the above copyright
//     notice, this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in
//     the documentation and/or other materials provided with the
//     distribution.
//   * Neither the name of the copyright holders nor the names of
//     contributors may be used to endorse or promote products derived
//     from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS'
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.
#include <catch.hpp>
#include <iostream>

#define __Mock_Mock__
#define ETLSTD etlstd
#include <libstd/include/memory>
#include <libstd/include/utility>

class MyClass {
public:
    MyClass(uint32_t id) : id(id) {
        instances++;
    }

    ~MyClass() {
        instances--;
    }
public:
    static uint8_t instances;
    uint32_t id;
};

uint8_t MyClass::instances = 0;
//using namespace etlTest::std;

SCENARIO("std::unique_ptr") {
    GIVEN("0 class instances") {
        MyClass::instances = 0;
        WHEN("a unique_ptr is created") {
            THEN("") {
                auto obj = ETLSTD::make_unique<MyClass>(123456);
                REQUIRE(MyClass::instances == 1);
                auto obj2 = ETLSTD::move(obj);
                REQUIRE(MyClass::instances == 1);
                REQUIRE(obj2->id == 123456);
            }
            REQUIRE(MyClass::instances == 0);
        }
    }
}

SCENARIO("std::shared_ptr") {
    GIVEN("A shared_ptr constructed by make_shared") {
        MyClass::instances = 0;
        auto obj = ETLSTD::make_shared<MyClass>(123456);
        REQUIRE(MyClass::instances == 1);

        WHEN("ptr is copied") {
            auto obj2 = obj;
            THEN("both points to the same object") {
                obj->id++;
                REQUIRE(obj2->id == obj->id);
                REQUIRE(obj.use_count() == 2);
            }
        }

        WHEN("ptr is copied twice") {
            auto obj2 = obj;
            auto obj3 = obj;
            THEN("3 references are counted")
                REQUIRE(obj.use_count() == 3);
            
            obj = nullptr;
            THEN("ref count is decreased") 
                REQUIRE(obj2.use_count() == 2);
            
            obj3.reset();
            REQUIRE(!obj3);
            REQUIRE(obj2.unique());
        }

    }
    REQUIRE(MyClass::instances == 0);
}
