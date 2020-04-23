#ifndef MEGA2_H_
#define MEGA2_H_

#include <vector>

#include "emulator/Device.h"

class ADB;
class VGC;

class Mega2 : public Device {
    friend class VGC;

    private:
        VGC *vgc = nullptr;
        ADB *adb = nullptr;

        unsigned int last_access = 0;

        bool sw_80store = false;
        bool sw_auxrd = false;
        bool sw_auxwr = false;
        bool sw_altzp = false;

        bool sw_lcbank2 = false;
        bool sw_lcread = false;
        bool sw_lcwrite = false;
        bool sw_lcsecond = false;

        bool sw_shadow_text = false;
        bool sw_shadow_text2 = false;
        bool sw_shadow_hires1 = false;
        bool sw_shadow_hires2 = false;
        bool sw_shadow_super = false;
        bool sw_shadow_aux = false;
        bool sw_shadow_lc = false;

        bool sw_slot_reg[8] = {false};

        bool sw_intcxrom = false;
        bool sw_slotc3rom = false;
        bool sw_rombank = false;

        uint8_t sw_diagtype = 0;

        bool sw_qtrsecirq_enable = false;
        bool sw_vblirq_enable = false;

        bool sw_slot7_motor = false;
        bool sw_slot6_motor = false;
        bool sw_slot5_motor = false;
        bool sw_slot4_motor = false;

        bool sw_annunciator[4] = {false};

        bool in_vbl = false;

        void updateMemoryMaps();
        void buildLanguageCard(unsigned int bank, unsigned int src_bank);

        std::vector<unsigned int>& ioReadList()
        {
            static std::vector<unsigned int> locs = {
                0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                0x09, 0x0A, 0x0B, 0x11, 0x12, 0x13, 0x14, 0x15,
                0x16, 0x17, 0x18, 0x19, 0x2D, 0x35, 0x36, 
                0x41, 0x46, 0x47, 
                0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 
                0x68, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 
                0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 
                0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
                0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F
            };

            return locs;
        }

        std::vector<unsigned int>& ioWriteList()
        {
            static std::vector<unsigned int> locs = {
                0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                0x08, 0x09, 0x0A, 0x0B, 0x19, 0x2D, 0x35, 0x36,
                0x41, 0x47,
                0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 
                0x68, 
                0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
                0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F
            };

            return locs;
        }

    public:
        bool sw_fastmode;

        Mega2() = default;
        ~Mega2() = default;

        void reset();
        uint8_t read(const unsigned int& offset);
        void write(const unsigned int& offset, const uint8_t& value);

        void tick(const unsigned int);
        void microtick(const unsigned int);
};

#endif // MEGA2_H_
