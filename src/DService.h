/*
 *  Modern Native AddIn
 *  Copyright (C) 2018  Infactum
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef DSERVICE_H
#define DSERVICE_H

#include <regex>
#include "Component.h"

class DService final : public Component {
public:
    const char *Version = u8"1.0.0";

    DService();

    static std::wregex regInit(const std::wstring& Pattern);

private:
    std::string extensionName() override;

    void message(const variant_t &msg);
    void sleep(const variant_t &delay);
    variant_t currentDate();

    // regex
    bool regSelect(variant_t &String, const variant_t &Query, variant_t &Result);
    //bool regTest(tVariant* Params, tVariant* Result);
    //bool regReplace(tVariant* Params, tVariant* Result);

    /* 
    // ++============== Sample ==============
    std::shared_ptr<variant_t> sample_property;
    variant_t add(const variant_t& a, const variant_t& b);
    void assign(variant_t& out);
    variant_t samplePropertyValue();
    // -- ============== Sample ==============
    */
};

#endif // DSERVICE_H
