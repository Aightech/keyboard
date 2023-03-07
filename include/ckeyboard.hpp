#ifndef __CKEYBOARD_HPP
#define __CKEYBOARD_HPP

#include <cstdint>
#include <fcntl.h>
#include <iostream>
#include <linux/input.h>
#include <linux/keyboard.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <vector>

#define KEYBOARD_DEV "/dev/input/js0"
#define EVENT_DEV ""

class cKeyboard
{

    public:
    cKeyboard(bool verbose = true) : m_verbose(verbose){};
    ~cKeyboard();

    void
    connect(const char *dev_path = KEYBOARD_DEV,
            const char *ev_path = EVENT_DEV);

    static void *
    loop(void *obj);

    void
    readEv();

    bool
    keyPressed(int n);
    uint32_t
    key_bytes();

    uint8_t
    getNbAxis()
    {
        return m_axes;
    };
    uint8_t
    getNbButtons()
    {
        return m_buttons;
    };

    private:
    pthread_t m_thread;
    bool m_active;
    int m_keyboard_fd;
    bool m_verbose = true;

    int m_event_fd;
    struct ff_effect m_effects[4];
    struct input_event m_play, m_gain;

    uint32_t m_version;
    uint8_t m_axes;
    uint8_t m_buttons;

    char m_name[256];

    void
    play_f(__u16 code, __s32 value);
};

#endif // __CKEYBOARD_HPP
