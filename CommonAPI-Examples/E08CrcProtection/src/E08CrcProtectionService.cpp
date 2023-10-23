// Copyright (C) 2022 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <thread>

#include <CommonAPI/CommonAPI.hpp>
#include "E08CrcProtectionStubImpl.hpp"

int main() {
    CommonAPI::Runtime::setProperty("LogContext", "E08S");
    CommonAPI::Runtime::setProperty("LogApplication", "E08S");
    CommonAPI::Runtime::setProperty("LibraryBase", "E08CrcProtection");

    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.Attributes";
    std::string connection = "service-sample";

    std::shared_ptr<E08CrcProtectionStubImpl> myService = std::make_shared<E08CrcProtectionStubImpl>();
    while (!runtime->registerService(domain, instance, myService, connection)) {
        std::cout << "Register Service failed, trying again in 100 milliseconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "Successfully Registered Service!" << std::endl;

    while (true) {
        myService->incCounter(); // Change value of attributes, see stub implementation
        std::cout << "Waiting for calls... (Abort with CTRL+C)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    return 0;
}
