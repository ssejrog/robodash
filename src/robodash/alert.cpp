#include "robodash/alert.hpp"
#include "robodash/detail/gui.hpp"
#include "robodash/detail/styles.h"
#include "robodash/view.hpp"

// ============================= Alert Callback ============================= //

void alert_cb(lv_event_t *event) {
	rd::View *view = (rd::View *)lv_event_get_user_data(event);
	if (valid_view(view)) view->focus();

	lv_obj_t *alert = lv_event_get_target(event);
	lv_obj_del(alert);

	if (lv_obj_get_child_cnt(alert_cont) == 0) {
		lv_obj_add_flag(alert_cont, LV_OBJ_FLAG_HIDDEN);
		hide_shade();
	}
}

// ============================ Helper Functions ============================ //

lv_obj_t *create_alert(std::string message, std::string subtext) {
	lv_obj_t *alert = lv_obj_create(alert_cont);
	lv_obj_set_width(alert, lv_pct(100));
	lv_obj_set_height(alert, LV_SIZE_CONTENT);

	lv_obj_add_style(alert, &style_alert, 0);

	std::string title = (subtext.empty()) ? "Alert" : "Alert · " + subtext;

	lv_obj_t *origin_label = lv_label_create(alert);
	lv_obj_align(origin_label, LV_ALIGN_TOP_LEFT, 0, 0);
	lv_obj_add_style(origin_label, &style_text_small, 0);
	lv_label_set_text(origin_label, title.c_str());

	lv_obj_t *alert_msg = lv_label_create(alert);
	lv_obj_align(alert_msg, LV_ALIGN_TOP_LEFT, 0, 18);
	lv_obj_set_width(alert_msg, lv_pct(100));
	lv_obj_add_style(alert_msg, &style_text_medium, 0);
	lv_label_set_long_mode(alert_msg, LV_LABEL_LONG_WRAP);
	lv_label_set_text(alert_msg, message.c_str());

	return alert;
}

// ============================ Alert Functions ============================ //

void rd::alert(std::string message, std::string title) {
	hide_menu();
	show_shade();

	lv_obj_clear_flag(alert_cont, LV_OBJ_FLAG_HIDDEN);

	create_alert(message, title);
}

void rd::alert(std::string message, rd::View &view) {
	hide_menu();
	show_shade();

	lv_obj_clear_flag(alert_cont, LV_OBJ_FLAG_HIDDEN);

	lv_obj_t *alert = create_alert(message, view.get_name());
	lv_obj_add_event_cb(alert, alert_cb, LV_EVENT_CLICKED, view);
}