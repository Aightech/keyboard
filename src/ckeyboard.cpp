#include "ckeyboard.hpp"
#include <strANSIseq.hpp>
#include <string.h>

#define LOG(...)             \
    if(m_verbose)            \
    {                        \
        printf(__VA_ARGS__); \
        fflush(stdout);      \
    }
using namespace ESC;


void cKeyboard::connect(const char *dev_path, const char *ev_path)
{
    m_active = true;
    std::string event_path = "/dev/input/event17";
    m_event_fd = open(event_path.c_str(), O_RDWR);
    if(m_event_fd > 0)
    {
        char test[256];
        ioctl(m_event_fd, EVIOCGNAME(sizeof(test)), test);
        LOG("\t\t%s %s\n\n", fstr("Keyboard:", {UNDERLINE}).c_str(),
            fstr(event_path, {BOLD}).c_str());

	LOG("led : %s \n", test);
	ioctl(m_event_fd, EVIOCGLED(sizeof(test)), test);
	LOG("led : %s \n", test);

        /* Set master gain to 100% if supported */
        // memset(&m_gain, 0, sizeof(m_gain));
        // m_gain.type = EV_LED;
        // m_gain.code = LED_CAPSL;
        // m_gain.value = 0xffff; /* [0, 0xFFFF]) */
        // write(m_event_fd, &m_gain, sizeof(m_gain));

	

        /* pulse Left rumbling effect */
        m_effects[0].type = EV_LED;
        m_effects[0].id = -1;
        m_effects[0].u.rumble.strong_magnitude = 0xffff;
        m_effects[0].u.rumble.weak_magnitude = 0;
        m_effects[0].replay.length = 200;
        m_effects[0].replay.delay = 0;
        ioctl(m_event_fd, EVIOCSFF, &m_effects[0]);

	// memset(&m_play, 0, sizeof(m_play));
    // m_play.type = EV_FF;
    // m_play.code = code;
    // m_play.value = value;
    // write(m_event_fd, (const void *)&m_play, sizeof(m_play));

        // /* pulse right rumbling effect */
        // m_effects[1].type = FF_RUMBLE;
        // m_effects[1].id = -1;
        // m_effects[1].u.rumble.strong_magnitude = 0;
        // m_effects[1].u.rumble.weak_magnitude = 0xffff;
        // m_effects[1].replay.length = 200;
        // m_effects[1].replay.delay = 0;
        // ioctl(m_event_fd, EVIOCSFF, &m_effects[1]);

        // /* long Left rumbling effect */
        // m_effects[2].type = FF_RUMBLE;
        // m_effects[2].id = -1;
        // m_effects[2].u.rumble.strong_magnitude = 0xffff;
        // m_effects[2].u.rumble.weak_magnitude = 0;
        // m_effects[2].replay.length = 60000;
        // m_effects[2].replay.delay = 0;
        // ioctl(m_event_fd, EVIOCSFF, &m_effects[2]);

        // /* long right rumbling effect */
        // m_effects[3].type = FF_RUMBLE;
        // m_effects[3].id = -1;
        // m_effects[3].u.rumble.strong_magnitude = 0;
        // m_effects[3].u.rumble.weak_magnitude = 0xffff;
        // m_effects[3].replay.length = 60000;
        // m_effects[3].replay.delay = 0;
        // ioctl(m_event_fd, EVIOCSFF, &m_effects[3]);
    }
    else
        throw std::string("No joystick event found at ") + ev_path;
}

cKeyboard::~cKeyboard()
{
}

void *cKeyboard::loop(void *obj)
{
    while(reinterpret_cast<cKeyboard *>(obj)->m_active)
        reinterpret_cast<cKeyboard *>(obj)->readEv();
    return nullptr;
}

void cKeyboard::readEv()
{
    // int bytes = read(m_joystick_fd, m_joystick_ev, sizeof(*m_joystick_ev));
    // if(bytes > 0)
    // {
    //     m_joystick_ev->type &= ~JS_EVENT_INIT;
    //     if(m_joystick_ev->type & JS_EVENT_BUTTON)
    //     {
    //         m_joystick_st->button[m_joystick_ev->number] = m_joystick_ev->value;
    //         if(m_joystick_ev->value)
    //             m_joystick_st->btn_b |= 1 << m_joystick_ev->number;
    //         else
    //             m_joystick_st->btn_b &= ~(1 << m_joystick_ev->number);
    //         //std::cout << "Buttons n° " << joystick_st->btn_b << " :" << joystick_st->button[joystick_ev->number] << std::endl;
    //     }
    //     if(m_joystick_ev->type & JS_EVENT_AXIS)
    //     {
    //         m_joystick_st->axis[m_joystick_ev->number] = m_joystick_ev->value;
    //         //std::cout << "Axis n° " << (int)joystick_ev->number << " :" << joystick_st->axis[joystick_ev->number] << std::endl;
    //     }
    // }
}
void cKeyboard::play_f(__u16 code, __s32 value)
{
    memset(&m_play, 0, sizeof(m_play));
    m_play.type = EV_FF;
    m_play.code = code;
    m_play.value = value;
    write(m_event_fd, (const void *)&m_play, sizeof(m_play));
}
