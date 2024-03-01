#ifndef DSERVICE_H
#define DSERVICE_H

#include "Component.h"

class DService final : public Component {
public:
    const char *Version = u8"1.0.0";

    DService();

private:
    std::string extensionName() override;

    void message(const variant_t &msg);
    void sleep(const variant_t &delay);
    variant_t currentDate();

    /* 
    std::shared_ptr<variant_t> sample_property;
    variant_t add(const variant_t& a, const variant_t& b);
    void assign(variant_t& out);
    variant_t samplePropertyValue();
    */
};

#endif // DSERVICE_H
