#pragma once

#include "../include/display/lvgl.h"
#include <cstdlib>

namespace Display {
    static inline lv_obj_t* lv_img_disp(const lv_img_dsc_t* cArr)
    {
        lv_obj_t* img = lv_img_create(lv_scr_act(), NULL);
        lv_img_set_src(img, cArr);
        lv_obj_align(img, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

        return img;
    }
    static inline lv_obj_t* createLabel(lv_obj_t* parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,const char* title) {
        lv_obj_t* label =  lv_label_create(parent, NULL);
        lv_obj_set_pos(label, x, y);
        lv_obj_set_size(label, width, height);
        lv_label_set_text(label,title);
        lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);

        return label;
    }
    static inline lv_style_t* createLabelSty(lv_style_t* copy, lv_color_t bgCol, lv_color_t textColor, unsigned char opa) {
        lv_style_t* labelSty;
        lv_style_copy(&labelSty[0], copy);

        labelSty[0].body.main_color = bgCol;
        labelSty[0].body.opa = opa;
        labelSty[0].text.color = textColor;

        return labelSty;
    }
    static inline lv_obj_t* createBtn(lv_obj_t* parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height, const char* title)
    {
        lv_obj_t* btn = lv_btn_create(parent, NULL);
        lv_obj_set_pos(btn, x, y);
        lv_obj_set_size(btn, width, height);

        lv_obj_t* label = lv_label_create(btn, NULL);
        lv_label_set_text(label, title);
        lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

        return btn;
    }
    static inline lv_style_t* createBtnStyle(lv_style_t* copy, lv_color_t rel, lv_color_t pr, lv_color_t tglRel, lv_color_t tglPr, lv_color_t textColor)
    {
        lv_style_t* btnStyle = (lv_style_t*)malloc(sizeof(lv_style_t)* 4);

        for(unsigned char i = 0; i < 4; i++) lv_style_copy(&btnStyle[i], copy);

        btnStyle[0].body.main_color = rel;
        btnStyle[0].body.grad_color = rel;
        btnStyle[0].text.color = textColor;

        btnStyle[1].body.main_color = pr;
        btnStyle[1].body.grad_color = pr;
        btnStyle[1].text.color = textColor;

        btnStyle[2].body.main_color = tglRel;
        btnStyle[2].body.grad_color = tglRel;
        btnStyle[2].text.color = textColor;

        btnStyle[3].body.main_color = tglPr;
        btnStyle[3].body.grad_color = tglPr;
        btnStyle[3].text.color = textColor;

        return btnStyle;
    }
    static inline void setBtnStyle(lv_style_t* btnStyle, lv_obj_t* btn)
    {
        lv_btn_set_style(btn, LV_BTN_STYLE_REL, &btnStyle[0]);
        lv_btn_set_style(btn, LV_BTN_STYLE_PR, &btnStyle[1]);
        lv_btn_set_style(btn, LV_BTN_STYLE_TGL_REL, &btnStyle[2]);
        lv_btn_set_style(btn, LV_BTN_STYLE_TGL_PR, &btnStyle[3]);
    }
    static inline void btnSetToggled(lv_obj_t* btn, bool toggled)
    {
        if(toggled != (lv_btn_get_state(btn) >= 2)) lv_btn_toggle(btn);
    }
};