#ifndef DSERVICE_H
#define DSERVICE_H

#include <regex>
#include "Component.h"

class DService final : public Component {
public:
    const char *Version = u8"1.0.0";

    DService();

    //static std::wregex regInit(const std::wstring& Pattern);

private:
    std::string extensionName() override;

    void message(const variant_t &msg);
    void sleep(const variant_t &delay);
    variant_t currentDate();

    //bool regSelect(variant_t &String, const variant_t &Query, variant_t &Result);
    //bool regTest(tVariant* Params, tVariant* Result);
    //bool regReplace(tVariant* Params, tVariant* Result);

    /* 
    std::shared_ptr<variant_t> sample_property;
    variant_t add(const variant_t& a, const variant_t& b);
    void assign(variant_t& out);
    variant_t samplePropertyValue();
    */
};

#endif // DSERVICE_H
