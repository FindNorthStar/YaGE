#include "core/window.h"
#include "dialog/message_dlg.h"
#include "platform/player.h"
#include <thread>
#include <cstdlib>
#include <iostream>
using namespace yage::core;
extern "C" int yage_main(void);

#define P_PROP(type, name, format) fprintf(stderr, #name"="#format", ", msg.type.name)
#define P_NAME(type) \
  case msg.type:\
fprintf(stderr, #type ": ")

#define P_STOP() \
  fprintf(stderr, "\n"); \
break

void test_message()
{
  Window w;
  w.show();

  Message msg;
  while (Window::poll(msg)) {
    switch (msg.type) {
      P_NAME(type_nop);
      P_STOP();

      P_NAME(type_kbd);
      P_PROP(kbd, is_press, %d);
      P_PROP(kbd, keyval, %u);
      P_PROP(kbd, keycode, %u);
      P_PROP(kbd, is_modkey, %u);
      P_PROP(kbd, modkey_alt, %u);
      P_PROP(kbd, modkey_ctrl, %u);
      P_PROP(kbd, modkey_shift, %u);
      P_STOP();

      P_NAME(type_mouse);
      P_PROP(mouse, x, %.1lf);
      P_PROP(mouse, y, %.1lf);
      P_PROP(mouse, type, %d);
      P_PROP(mouse, is_left, %u);
      P_PROP(mouse, is_right, %u);
      P_PROP(mouse, is_middle, %u);
      P_PROP(mouse, modkey_alt, %u);
      P_PROP(mouse, modkey_ctrl, %u);
      P_PROP(mouse, modkey_shift, %u);
      P_STOP();

      P_NAME(type_window);
      P_PROP(window, type, %d);
      P_STOP();

      default:
      break;
    }
  }
  fprintf(stderr, "test_message: Bye!\n");
}

void test_window_count(void)
{
  Window w;
  w.show();
  w.set_title("Window count test");
  char buf[20];
  int n = 0;

  Message msg;
  while (Window::poll(msg)) {
    if (msg.type != msg.type_mouse) continue;
    if (msg.mouse.type != msg.mouse.type_press) continue;
    if (msg.mouse.is_left) {
      Window *new_win = new Window;
      new_win->show();
      #ifndef _MSC_VER
      snprintf(buf, sizeof(buf), "Window %d", ++n);
      #else
      _snprintf(buf, sizeof(buf), "Window %d", ++n);
      #endif
      new_win->set_title(buf);
    }
    if (msg.mouse.is_right) msg.source->destroy();
  }
  fprintf(stderr, "test_window_count: Bye!\n");
}

void test_draw(void)
{
  Window w;
  w.show();

  Message msg;
  while (Window::poll(msg)) {
    if (msg.type != msg.type_mouse) continue;
    if (msg.mouse.type != msg.mouse.type_move) continue;
    if (!msg.mouse.is_left) continue;
    cairo_t *cr = cairo_create(w.pro_get_cairo_suface());
    cairo_rectangle(cr, msg.mouse.x - 3, msg.mouse.y - 3, 6, 6);
    cairo_fill(cr);
    cairo_destroy(cr);
    gtk_widget_queue_draw_area(w.pro_get_gtk_draw(), msg.mouse.x - 3, msg.mouse.y - 3, 6, 6);
  }
}

void test_resize()
{
  Window w;
  bool resize = false;
  w.show();
  int x = 300, y = 300;

  Message msg;
  while (Window::poll(msg)) {
    if (msg.type != msg.type_kbd) continue;
    if (!msg.kbd.is_press) continue;

    switch (msg.kbd.keyval) {
      case 't':
        resize = !resize;
        w.set_resizable(resize);
        fprintf(stderr, "Allow resize: %d\n", resize);
        break;

      case 'x':
        x -= 100;
        w.set_size(x, y);
        break;

      case 'X':
        x += 100;
        w.set_size(x, y);
        break;

      case 'y':
        y -= 100;
        w.set_size(x, y);
        break;

      case 'Y':
        y += 100;
        w.set_size(x, y);
        break;

      case 'q':
        fprintf(stderr, "x = %d, y = %d, ", x, y);
        w.get_size(x, y);
        fprintf(stderr, "nx = %d, ny = %d\n", x, y);
        break;

      case '!':
        w.hide();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        w.show();
    }
  }
}

void test_fix_size()
{
  Window w;
  w.show();
  Message msg;

  Window *t = nullptr;
  while (Window::poll(msg)) {
    if (msg.type != msg.type_kbd) continue;
    if (!msg.kbd.is_press) continue;

    switch (msg.kbd.keyval) {
      case 'a':
        if (t) delete t;
        t = new Window;
        t->show();
        fprintf(stderr, "show\n");
        break;

      case 'b':
        if (t) delete t;
        t = new Window;
        t->show();
        t->set_size(100, 200);
        fprintf(stderr, "show, set_size\n");
        break;

      case 'c':
        if (t) delete t;
        t = new Window;
        t->set_resizable(true);
        t->set_size(100, 200);
        t->show();
        fprintf(stderr, "set_res, set_size, show\n");
        break;

      case 'd':
        if (t) delete t;
        t = new Window;
        t->set_size(100, 200);
        t->set_resizable(true);
        t->show();
        fprintf(stderr, "set_size, set_res, show\n");
        break;

      case 'e':
        if (t) delete t;
        t = new Window;
        t->set_size(100, 200);
        t->show();
        t->set_resizable(true);
        fprintf(stderr, "set_size, show, set_res\n");
        break;

      case 'f':
        if (t) delete t;
        t = new Window;
        t->set_resizable(true);
        t->show();
        t->set_size(100, 200);
        fprintf(stderr, "set_res, show, set_size\n");
        break;

      case 'g':
        if (t) delete t;
        t = new Window;
        t->show();
        t->set_resizable(true);
        t->set_size(100, 200);
        fprintf(stderr, "show, set_res, set_size\n");
        break;

      case 'h':
        if (t) delete t;
        t = new Window;
        t->show();
        t->set_size(100, 200);
        t->set_resizable(true);
        fprintf(stderr, "show, set_size, set_res\n");
        break;

    }
  }
}

void test_dialog()
{
  using namespace yage::dialog;
  Window w;
  w.show();
  Message msg;

  while (Window::poll(msg)) {
    if (msg.type != msg.type_kbd) continue;
    if (!msg.kbd.is_press) continue;

    switch (msg.kbd.keyval) {
      case 'm':
        MessageDlg dlg(MessageDlg::button_type_yes_no, MessageDlg::icon_type_question, w);
        dlg.set_title("<u>title</u>");
        dlg.set_message("<i>message: press a button</i>");
        MessageDlg another_dlg(MessageDlg::button_type_ok, MessageDlg::icon_type_info);
        another_dlg.set_title("result");
        if (dlg.show() == MessageDlg::result_type_yes) {
          another_dlg.set_message("yes");
        } else {
          another_dlg.set_message("no");
        }
        another_dlg.show();
    }
  }
}

void test_audio(void) {
    using yage::platform::Player;
    std::cerr << "Load file IGNITE from Internet" << std::endl;
    Player *player = Player::create_player("https://kirito.me/ignite.mp3");
    std::cerr << "Play IGNITE" << std::endl;
	player->play();
	std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cerr << "Load file Date A Live from Internet" << std::endl;
	Player *player2 = Player::create_player("https://kirito.me/date_a_live.mp3");
    std::cerr << "Play Date A Live" << std::endl;
	player2->play();
	std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cerr << "Stop IGNITE" << std::endl;
    player->stop();
    std::cerr << "Destroy music IGNITE object" << std::endl;
	delete player;
	std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cerr << "Stop Date A Live" << std::endl;
	player2->stop();
    std::cerr << "Destroy music Date A Live object" << std::endl;
	delete player2;
}

int yage_main()
{
  test_audio();
  return 0;
}
