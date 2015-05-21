#include "test.h"
#include "../dialog/message_dlg.h"
#include "../dialog/file_chooser_dlg.h"
#include "../dialog/color_chooser_dlg.h"
#include "../dialog/font_chooser_dlg.h"
#include "../dialog/input_dlg.h"
using namespace yage::dialog;

void test_dialog_msg(Window &w)
{
  MessageDlg msg_dlg(MessageDlg::button_type_yes_no, MessageDlg::icon_type_question, w);
  msg_dlg.set_title("<u>title</u>");
  msg_dlg.set_message("<i>message: press a button</i>");
  MessageDlg msg_dlg1(MessageDlg::button_type_ok, MessageDlg::icon_type_info, w);
  msg_dlg1.set_title("result");
  if (msg_dlg.show() == MessageDlg::result_type_yes) {
    msg_dlg1.set_message("yes");
  } else {
    msg_dlg1.set_message("no");
  }
  msg_dlg1.show();
}

void test_dialog_fc(FileChooserDlg::action_type type, Window &w)
{
  FileChooserDlg fc_dlg(type, "fc_dlg", w);
  std::string path;
  if (fc_dlg.show(path)) {
    fprintf(stderr, "Path: %s\n", path.c_str());
  }
}

void test_dialog_input(Window &w)
{
  std::string msg = "Aloha World!";
  bool ok = true;
  while (ok) {
    InputDlg input_dlg("input_dlg", w);
    input_dlg.set_message(msg.c_str());
    ok = input_dlg.show(msg);
  }
}

void test_dialog_color_font(Window &w)
{
  ColorChooserDlg color_dlg("color", w);
  FontChooserDlg font_dlg("font", w);

  yage::draw::Color color;
  yage::draw::Font font;

  color_dlg.show(color);
  font_dlg.show(font);

  yage::draw::Text text("Yet another Graphics Engine", font);
  text.position = yage::draw::Point(0, 0);
  text.color = color;

  w.get_canvas()->draw_text(text);
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
      case 'a':
        test_dialog_msg(w);
        break;

      case 'b':
        test_dialog_fc(FileChooserDlg::action_type_open, w);
        break;

      case 'c':
        test_dialog_fc(FileChooserDlg::action_type_save, w);
        break;

      case 'd':
        test_dialog_fc(FileChooserDlg::action_type_create_folder, w);
        break;

      case 'e':
        test_dialog_fc(FileChooserDlg::action_type_select_folder, w);
        break;

      case 'f':
        test_dialog_color_font(w);
        break;

      case 'g':
        test_dialog_input(w);
        break;
    }
  }
}

