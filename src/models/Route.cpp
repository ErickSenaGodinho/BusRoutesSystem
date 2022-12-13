#pragma once
#include "Route.hpp"

Route::Route() {}

Route::~Route() {}

void Route::setCode(std::string code)
{
    strcpy(this->code, code.c_str());
}

void Route::setCompany(std::string company)
{
    strcpy(this->company, company.c_str());
}