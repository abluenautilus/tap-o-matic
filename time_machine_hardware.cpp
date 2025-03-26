#include "time_machine_hardware.h"
#include <vector>

namespace oam
{
namespace time_machine
{
    /** Const definitions */
    constexpr Pin DUMMYPIN        = Pin(PORTX, 0);
    constexpr Pin PIN_ADC_CTRL_1  = DaisyPatchSM::C5;
    constexpr Pin PIN_ADC_CTRL_2  = DaisyPatchSM::C4;
    constexpr Pin PIN_ADC_CTRL_3  = DaisyPatchSM::C3;
    constexpr Pin PIN_ADC_CTRL_4  = DaisyPatchSM::C2;
    constexpr Pin PIN_ADC_CTRL_5  = DaisyPatchSM::C6;
    constexpr Pin PIN_ADC_CTRL_6  = DaisyPatchSM::C7;
    constexpr Pin PIN_ADC_CTRL_7  = DaisyPatchSM::C8;
    constexpr Pin PIN_ADC_CTRL_8  = DaisyPatchSM::C9;
    constexpr Pin PIN_ADC_CTRL_9  = DaisyPatchSM::A2;
    constexpr Pin PIN_ADC_CTRL_10 = DaisyPatchSM::A3;
    constexpr Pin PIN_ADC_CTRL_11 = DaisyPatchSM::D9;
    constexpr Pin PIN_ADC_CTRL_12 = DaisyPatchSM::D8;
    constexpr Pin PIN_USER_LED    = Pin(PORTC, 7);

    constexpr Pin kPinMap[4][10] =
        // Bank A
        {{DaisyPatchSM::A1,
          DaisyPatchSM::A2,
          DaisyPatchSM::A3,
          DaisyPatchSM::A4,
          DaisyPatchSM::A5,
          DaisyPatchSM::A6,
          DaisyPatchSM::A7,
          DaisyPatchSM::A8,
          DaisyPatchSM::A9,
          DaisyPatchSM::A10},

         // Bank B
         {DaisyPatchSM::B1,
          DaisyPatchSM::B2,
          DaisyPatchSM::B3,
          DaisyPatchSM::B4,
          DaisyPatchSM::B5,
          DaisyPatchSM::B6,
          DaisyPatchSM::B7,
          DaisyPatchSM::B8,
          DaisyPatchSM::B9,
          DaisyPatchSM::B10},

         // Bank C
         {DaisyPatchSM::C1,
          DaisyPatchSM::C2,
          DaisyPatchSM::C3,
          DaisyPatchSM::C4,
          DaisyPatchSM::C5,
          DaisyPatchSM::C6,
          DaisyPatchSM::C7,
          DaisyPatchSM::C8,
          DaisyPatchSM::C9,
          DaisyPatchSM::C10},

         // Bank D
         {DaisyPatchSM::D1,
          DaisyPatchSM::D2,
          DaisyPatchSM::D3,
          DaisyPatchSM::D4,
          DaisyPatchSM::D5,
          DaisyPatchSM::D6,
          DaisyPatchSM::D7,
          DaisyPatchSM::D8,
          DaisyPatchSM::D9,
          DaisyPatchSM::D10}};

    const Pin TimeMachineHardware::A1  = kPinMap[0][0];
    const Pin TimeMachineHardware::A2  = kPinMap[0][1];
    const Pin TimeMachineHardware::A3  = kPinMap[0][2];
    const Pin TimeMachineHardware::A4  = kPinMap[0][3];
    const Pin TimeMachineHardware::A5  = kPinMap[0][4];
    const Pin TimeMachineHardware::A6  = kPinMap[0][5];
    const Pin TimeMachineHardware::A7  = kPinMap[0][6];
    const Pin TimeMachineHardware::A8  = kPinMap[0][7];
    const Pin TimeMachineHardware::A9  = kPinMap[0][8];
    const Pin TimeMachineHardware::A10 = kPinMap[0][9];
    const Pin TimeMachineHardware::B1  = kPinMap[1][0];
    const Pin TimeMachineHardware::B2  = kPinMap[1][1];
    const Pin TimeMachineHardware::B3  = kPinMap[1][2];
    const Pin TimeMachineHardware::B4  = kPinMap[1][3];
    const Pin TimeMachineHardware::B5  = kPinMap[1][4];
    const Pin TimeMachineHardware::B6  = kPinMap[1][5];
    const Pin TimeMachineHardware::B7  = kPinMap[1][6];
    const Pin TimeMachineHardware::B8  = kPinMap[1][7];
    const Pin TimeMachineHardware::B9  = kPinMap[1][8];
    const Pin TimeMachineHardware::B10 = kPinMap[1][9];
    const Pin TimeMachineHardware::C1  = kPinMap[2][0];
    const Pin TimeMachineHardware::C2  = kPinMap[2][1];
    const Pin TimeMachineHardware::C3  = kPinMap[2][2];
    const Pin TimeMachineHardware::C4  = kPinMap[2][3];
    const Pin TimeMachineHardware::C5  = kPinMap[2][4];
    const Pin TimeMachineHardware::C6  = kPinMap[2][5];
    const Pin TimeMachineHardware::C7  = kPinMap[2][6];
    const Pin TimeMachineHardware::C8  = kPinMap[2][7];
    const Pin TimeMachineHardware::C9  = kPinMap[2][8];
    const Pin TimeMachineHardware::C10 = kPinMap[2][9];
    const Pin TimeMachineHardware::D1  = kPinMap[3][0];
    const Pin TimeMachineHardware::D2  = kPinMap[3][1];
    const Pin TimeMachineHardware::D3  = kPinMap[3][2];
    const Pin TimeMachineHardware::D4  = kPinMap[3][3];
    const Pin TimeMachineHardware::D5  = kPinMap[3][4];
    const Pin TimeMachineHardware::D6  = kPinMap[3][5];
    const Pin TimeMachineHardware::D7  = kPinMap[3][6];
    const Pin TimeMachineHardware::D8  = kPinMap[3][7];
    const Pin TimeMachineHardware::D9  = kPinMap[3][8];
    const Pin TimeMachineHardware::D10 = kPinMap[3][9];

    /** outside of class static buffer(s) for DMA access */
    uint16_t DMA_BUFFER_MEM_SECTION dsy_patch_sm_dac_buffer[2][48];

    class TimeMachineHardware::Impl
    {
      public:
        Impl()
        {
            dac_running_            = false;
            dac_buffer_size_        = 48;
            dac_output_[0]          = 0;
            dac_output_[1]          = 0;
            internal_dac_buffer_[0] = dsy_patch_sm_dac_buffer[0];
            internal_dac_buffer_[1] = dsy_patch_sm_dac_buffer[1];
        }

        void InitDac();

        void StartDac(DacHandle::DacCallback callback);

        void StopDac();

        static void InternalDacCallback(uint16_t **output, size_t size);

        /** Based on a 0-5V output with a 0-4095 12-bit DAC */
        static inline uint16_t VoltageToCode(float input)
        {
            float pre = input * 819.f;
            if(pre > 4095.f)
                pre = 4095.f;
            else if(pre < 0.f)
                pre = 0.f;
            return (uint16_t)pre;
        }

        inline void WriteCvOut(int channel, float voltage)
        {
            if(channel == 0 || channel == 1)
                dac_output_[0] = VoltageToCode(voltage);
            if(channel == 0 || channel == 2)
                dac_output_[1] = VoltageToCode(voltage);
        }

        size_t    dac_buffer_size_;
        uint16_t *internal_dac_buffer_[2];
        uint16_t  dac_output_[2];
        DacHandle dac_;

      private:
        bool dac_running_;
    };

    /** Static Local Object */
    static TimeMachineHardware::Impl patch_sm_hw;

    /** Impl function definintions */

    void TimeMachineHardware::Impl::InitDac()
    {
        DacHandle::Config dac_config;
        dac_config.mode     = DacHandle::Mode::DMA;
        dac_config.bitdepth = DacHandle::BitDepth::
            BITS_12; /**< Sets the output value to 0-4095 */
        dac_config.chn               = DacHandle::Channel::BOTH;
        dac_config.buff_state        = DacHandle::BufferState::ENABLED;
        dac_config.target_samplerate = 48000;
        dac_.Init(dac_config);
    }

    void TimeMachineHardware::Impl::StartDac(DacHandle::DacCallback callback)
    {
        if(dac_running_)
            dac_.Stop();
        dac_.Start(internal_dac_buffer_[0],
                   internal_dac_buffer_[1],
                   dac_buffer_size_,
                   callback == nullptr ? InternalDacCallback : callback);
        dac_running_ = true;
    }

    void TimeMachineHardware::Impl::StopDac()
    {
        dac_.Stop();
        dac_running_ = false;
    }


    void TimeMachineHardware::Impl::InternalDacCallback(uint16_t **output, size_t size)
    {
        /** We could add some smoothing, interp, or something to make this a bit less waste-y */
        // std::fill(&output[0][0], &output[0][size], patch_sm_hw.dac_output_[0]);
        // std::fill(&output[1][1], &output[1][size], patch_sm_hw.dac_output_[1]);
        for(size_t i = 0; i < size; i++)
        {
            output[0][i] = patch_sm_hw.dac_output_[0];
            output[1][i] = patch_sm_hw.dac_output_[1];
        }
    }

/** Actual TimeMachineHardware implementation
 *  With the pimpl model in place, we can/should probably
 *  move the rest of the implementation to the Impl class
 */

    void TimeMachineHardware::Init()
    {
        /** Assign pimpl pointer */
        pimpl_ = &patch_sm_hw;
        /** Initialize the MCU and clock tree */
        System::Config syscfg;
        syscfg.Boost();

        auto memory = System::GetProgramMemoryRegion();
        if (memory != System::MemoryRegion::INTERNAL_FLASH)
        {
            syscfg.skip_clocks = true;
        }

        system.Init(syscfg);

        /** Memories */
        if (memory == System::MemoryRegion::INTERNAL_FLASH)
        {
            /** FMC SDRAM */
            sdram.Init();
        }

        if (memory != System::MemoryRegion::QSPI)
        {
            /** QUADSPI FLASH */
            QSPIHandle::Config qspi_config;
            qspi_config.device = QSPIHandle::Config::Device::IS25LP064A;
            qspi_config.mode   = QSPIHandle::Config::Mode::MEMORY_MAPPED;
            qspi_config.pin_config.io0 = Pin(PORTF, 8);
            qspi_config.pin_config.io1 = Pin(PORTF, 9);
            qspi_config.pin_config.io2 = Pin(PORTF, 7);
            qspi_config.pin_config.io3 = Pin(PORTF, 6);
            qspi_config.pin_config.clk = Pin(PORTF, 10);
            qspi_config.pin_config.ncs = Pin(PORTG, 6);
            qspi.Init(qspi_config);
        }

        /** Audio */

        // Audio Init
        SaiHandle::Config sai_config;
        sai_config.periph          = SaiHandle::Config::Peripheral::SAI_1;
        sai_config.sr              = SaiHandle::Config::SampleRate::SAI_48KHZ;
        sai_config.bit_depth       = SaiHandle::Config::BitDepth::SAI_24BIT;
        sai_config.a_sync          = SaiHandle::Config::Sync::MASTER;
        sai_config.b_sync          = SaiHandle::Config::Sync::SLAVE;
        sai_config.a_dir           = SaiHandle::Config::Direction::RECEIVE;
        sai_config.b_dir           = SaiHandle::Config::Direction::TRANSMIT;
        sai_config.pin_config.fs   = Pin(PORTE, 4);
        sai_config.pin_config.mclk = Pin(PORTE, 2);
        sai_config.pin_config.sck  = Pin(PORTE, 5);
        sai_config.pin_config.sa   = Pin(PORTE, 6);
        sai_config.pin_config.sb   = Pin(PORTE, 3);
        SaiHandle sai_1_handle;
        sai_1_handle.Init(sai_config);

        I2CHandle::Config i2c_cfg;
        i2c_cfg.periph         = I2CHandle::Config::Peripheral::I2C_2;
        i2c_cfg.mode           = I2CHandle::Config::Mode::I2C_MASTER;
        i2c_cfg.speed          = I2CHandle::Config::Speed::I2C_400KHZ;
        i2c_cfg.pin_config.scl = Pin(PORTB, 10);
        i2c_cfg.pin_config.sda = Pin(PORTB, 11);
        I2CHandle i2c2;
        i2c2.Init(i2c_cfg);
        codec.Init(i2c2);

        AudioHandle::Config audio_config;
        audio_config.blocksize  = 48;
        audio_config.samplerate = SaiHandle::Config::SampleRate::SAI_48KHZ;
        audio_config.postgain   = 1.f;
        audio.Init(audio_config, sai_1_handle);
        callback_rate_ = AudioSampleRate() / AudioBlockSize();

        /** ADC Init */
        AdcChannelConfig adc_config[ADC_LAST + 7];

        /** Order of pins to match enum expectations */
        Pin adc_pins[] = {
            PIN_ADC_CTRL_1,
            PIN_ADC_CTRL_2,
            PIN_ADC_CTRL_3,
            PIN_ADC_CTRL_4,
            PIN_ADC_CTRL_8,
            PIN_ADC_CTRL_7,
            PIN_ADC_CTRL_5,
            PIN_ADC_CTRL_6,
            PIN_ADC_CTRL_9,
            PIN_ADC_CTRL_10,
            PIN_ADC_CTRL_11,
            PIN_ADC_CTRL_12
        };

        for (int i = 0; i < ADC_LAST; i++)
        {
            switch (i)
            {
                case CV_1:
                case ADC_10:
                case ADC_11:
                case ADC_12:
                    adc_config[i].InitMux(adc_pins[i], 8, MUX_A, MUX_B, MUX_C);
                    break;

                default:
                    adc_config[i].InitSingle(adc_pins[i]);
                    break;
            }
        }

        adc.Init(adc_config, ADC_LAST);

        /** Control Init */
        for (size_t i = 0; i < ADC_LAST; i++)
        {
            switch (i) {
                case CV_1:
                    for(int muxChannel = 0; muxChannel < 8; muxChannel++) {
                        controls[i].InitBipolarCv(adc.GetMuxPtr(i, muxChannel), callback_rate_);
                    }
                    break;

                case CV_2:
                case CV_3:
                case CV_4:
                case CV_5:
                case CV_6:
                case CV_7:
                case CV_8:
                    controls[i].InitBipolarCv(adc.GetPtr(i), callback_rate_);
                    break;

                case ADC_9:
                    controls[i].Init(adc.GetPtr(i), callback_rate_);
                    break;

                case ADC_10:
                case ADC_11:
                case ADC_12:
                    for(int muxChannel = 0; muxChannel < 8; muxChannel++) {
                        controls[i].Init(adc.GetMuxPtr(i, muxChannel), callback_rate_);
                    }
                    break;
            }
        }

        /** Fixed-function Digital I/O */
        user_led.Init(PIN_USER_LED, GPIO::Mode::OUTPUT);

        gate_in_1.Init(B10);
        gate_in_2.Init(B9);

        /** DAC init */
        pimpl_->InitDac();

        /** Start any background stuff */
        StartAdc();
        StartDac();
    }

    void TimeMachineHardware::StartAudio(AudioHandle::AudioCallback cb)
    {
        audio.Start(cb);
    }

    void TimeMachineHardware::StartAudio(AudioHandle::InterleavingAudioCallback cb)
    {
        audio.Start(cb);
    }

    void TimeMachineHardware::ChangeAudioCallback(AudioHandle::AudioCallback cb)
    {
        audio.ChangeCallback(cb);
    }

    void TimeMachineHardware::ChangeAudioCallback(AudioHandle::InterleavingAudioCallback cb)
    {
        audio.ChangeCallback(cb);
    }

    void TimeMachineHardware::StopAudio() { audio.Stop(); }

    void TimeMachineHardware::SetAudioBlockSize(size_t size)
    {
        audio.SetBlockSize(size);
        callback_rate_ = AudioSampleRate() / AudioBlockSize();
        for (size_t i = 0; i < ADC_LAST; i++)
        {
            controls[i].SetSampleRate(callback_rate_);
        }
    }

    void TimeMachineHardware::SetAudioSampleRate(float sr)
    {
        SaiHandle::Config::SampleRate sai_sr;
        switch (int(sr))
        {
            case 8000:
                sai_sr = SaiHandle::Config::SampleRate::SAI_8KHZ;
                break;

            case 16000:
                sai_sr = SaiHandle::Config::SampleRate::SAI_16KHZ;
                break;

            case 32000:
                sai_sr = SaiHandle::Config::SampleRate::SAI_32KHZ;
                break;

            case 48000:
                sai_sr = SaiHandle::Config::SampleRate::SAI_48KHZ;
                break;

            case 96000:
                sai_sr = SaiHandle::Config::SampleRate::SAI_96KHZ;
                break;

            default:
                sai_sr = SaiHandle::Config::SampleRate::SAI_48KHZ;
                break;
        }

        audio.SetSampleRate(sai_sr);
        callback_rate_ = AudioSampleRate() / AudioBlockSize();
        for (size_t i = 0; i < ADC_LAST; i++)
        {
            controls[i].SetSampleRate(callback_rate_);
        }
    }

    void TimeMachineHardware::SetAudioSampleRate(SaiHandle::Config::SampleRate sample_rate)
    {
        audio.SetSampleRate(sample_rate);
        callback_rate_ = AudioSampleRate() / AudioBlockSize();
        for (size_t i = 0; i < ADC_LAST; i++)
        {
            controls[i].SetSampleRate(callback_rate_);
        }
    }

    size_t TimeMachineHardware::AudioBlockSize()
    {
        return audio.GetConfig().blocksize;
    }

    float TimeMachineHardware::AudioSampleRate() { return audio.GetSampleRate(); }

    float TimeMachineHardware::AudioCallbackRate() { return callback_rate_; }

    void TimeMachineHardware::StartAdc() { adc.Start(); }

    void TimeMachineHardware::StopAdc() { adc.Stop(); }

    void TimeMachineHardware::ProcessAnalogControls()
    {
        for (int i = 0; i < ADC_LAST; i++)
        {
            controls[i].Process();
        }
    }

    void TimeMachineHardware::ProcessDigitalControls() {}

    float TimeMachineHardware::GetAdcValue(int idx) { return controls[idx].Value(); }

    float TimeMachineHardware::GetLevelSlider(int idx) {
        const int muxMapping[] = {5, 7, 6, 4, 3, 0, 1, 2};

        if (idx == 0) {
            return 1.0 - adc.GetMuxFloat(MISC_MUX, 3);
        } else {
            return 1.0 - adc.GetMuxFloat(LEVEL_MUX, muxMapping[idx - 1]);
        }
    }

    float TimeMachineHardware::GetLevelCV(int idx) {
        const int muxMapping[] = {3, 2, 1, 0, 4, 5, 6, 7};

        if (idx == 0)
        {
            return GetAdcValue(LEVEL_DRY_CV);
        }
        else
        {
            return ((1.0 - adc.GetMuxFloat(LEVEL_CV_MUX, muxMapping[idx - 1])) * 2.0) - 1.0;
        }
    }

    float TimeMachineHardware::GetPanKnob(int idx) {
        const int muxMapping[] = {5, 7, 6, 4, 1, 2, 0, 3};

        // The '1.0 - x' bit here is because our pan pots are wired backwards!
        if (idx == 0)
        {
            return 1.0 - adc.GetMuxFloat(MISC_MUX, 6);
        }
        else
        {
            return 1.0 - adc.GetMuxFloat(PAN_MUX, muxMapping[idx - 1]);
        }
    }

    float TimeMachineHardware::GetSpreadKnob()
    {
        return adc.GetMuxFloat(MISC_MUX, 2);
    }

    float TimeMachineHardware::GetTimeKnob()
    {
        return adc.GetMuxFloat(MISC_MUX, 4);
    }

    float TimeMachineHardware::GetFeedbackKnob()
    {
        return adc.GetMuxFloat(MISC_MUX, 1);
    }

    float TimeMachineHardware::GetHighpassKnob()
    {
        return adc.GetMuxFloat(MISC_MUX, 0);
    }

    float TimeMachineHardware::GetLowpassKnob()
    {
        return adc.GetMuxFloat(MISC_MUX, 5);
    }

    Pin TimeMachineHardware::GetPin(const PinBank bank, const int idx)
    {
        if(idx <= 0 || idx > 10)
        {
            return DUMMYPIN;
        }
        else
        {
            return kPinMap[static_cast<int>(bank)][idx - 1];
        }
    }

    void TimeMachineHardware::StartDac(DacHandle::DacCallback callback)
    {
        pimpl_->StartDac(callback);
    }

    void TimeMachineHardware::StopDac() { pimpl_->StopDac(); }

    void TimeMachineHardware::WriteCvOut(const int channel, float voltage)
    {
        pimpl_->WriteCvOut(channel, voltage);
    }

    void TimeMachineHardware::SetLed(bool state) {  user_led.Write(state); }

    bool TimeMachineHardware::ValidateSDRAM()
    {
        uint32_t *sdramptr      = (uint32_t *)0xc0000000;
        uint32_t  size_in_words = 16777216;
        uint32_t  testval       = 0xdeadbeef;
        uint32_t  num_failed    = 0;

        /** Write test val */
        for (uint32_t i = 0; i < size_in_words; i++)
        {
            uint32_t *word = sdramptr + i;
            *word          = testval;
        }

        /** Compare written */
        for (uint32_t i = 0; i < size_in_words; i++)
        {
            uint32_t *word = sdramptr + i;
            if (*word != testval)
            {
                num_failed++;
            }
        }

        /** Write Zeroes */
        for (uint32_t i = 0; i < size_in_words; i++)
        {
            uint32_t *word = sdramptr + i;
            *word = 0x00000000;
        }

        /** Compare Cleared */
        for (uint32_t i = 0; i < size_in_words; i++)
        {
            uint32_t *word = sdramptr + i;
            if (*word != 0) {
                num_failed++;
            }
        }

        return num_failed == 0;
    }

    bool TimeMachineHardware::ValidateQSPI(bool quick)
    {
        uint32_t start;
        uint32_t size;
        if (quick)
        {
            start = 0x400000;
            size  = 0x4000;
        }
        else
        {
            start = 0;
            size  = 0x800000;
        }
        // Erase the section to be tested
        qspi.Erase(start, start + size);

        // Create some test data
        std::vector<uint8_t> test;
        test.resize(size);
        uint8_t *testmem = test.data();

        for (size_t i = 0; i < size; i++) {
            testmem[i] = (uint8_t) (i & 0xff);
        }

        // Write the test data to the device
        qspi.Write(start, size, testmem);

        // Read it all back and count any/all errors
        // I supppose any byte where ((data & 0xff) == data)
        // would be able to false-pass..

        size_t fail_cnt = 0;

        for (size_t i = 0; i < size; i++)
        {
            if (testmem[i] != (uint8_t) (i & 0xff)) {
                fail_cnt++;
            }
        }

        return fail_cnt == 0;
    }

} // namespace patch_sm

} // namespace daisy