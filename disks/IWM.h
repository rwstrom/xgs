#ifndef IWM_H_
#define IWM_H_

#include "emulator/Device.h"

#include "disks/Disk35.h"
#include "disks/Disk525.h"

class Mega2;

class IWM : public Device {
    friend class Mega2;

    public:
        IWM();
        ~IWM();

        void reset();
        std::uint8_t read(const unsigned int& offset);
        void write(const unsigned int& offset, const std::uint8_t& value);

        void tick(const unsigned int);

        void loadDrive(const unsigned int, const unsigned int, VirtualDisk *);
        void unloadDrive(const unsigned int, const unsigned int);

        // Return the ID of the drive whose motor is on,  as 0xsd where
        // s = slot (5 or 6) and d = drive (0 or 1). Returns 0 if the motor
        // is not currently on

        const unsigned int getMotorState() {
            if (iwm_motor_on) {
                return (iwm_35sel? 0x50 : 0x60) | iwm_drive_select;
            }
            else {
                return 0;
            }
        }

    private:
        static const unsigned int kNumDevices = 4;

        std::vector<unsigned int>& ioReadList()
        {
            static std::vector<unsigned int> locs = {
                0x31,
                0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 
                0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF 
            };

            return locs;
        }

        std::vector<unsigned int>& ioWriteList()
        {
            static std::vector<unsigned int> locs = {
                0x31,
                0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 
                0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF 
            };

            return locs;
        }

        Disk525 disks_525[2];
        Disk35  disks_35[2];

        bool slot4_motor;
        bool slot5_motor;
        bool slot6_motor;
        bool slot7_motor;

        bool iwm_motor_on;
        bool iwm_motor_spindown;

        unsigned int motor_off_frame;

        bool iwm_q6;
        bool iwm_q7;

        bool iwm_enable2;
        unsigned int iwm_enable2_handshake = 0;

        bool iwm_phase[4];
        int iwm_mode;
        int iwm_drive_select;
        int iwm_reset;

        bool iwm_35sel = false;
        bool iwm_35ctl = false;

        void touchSwitches(const unsigned int);
};

#endif // IWM_H_
