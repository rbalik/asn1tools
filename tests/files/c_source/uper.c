/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Erik Moqvist
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * This file was generated by asn1tools version 0.138.2 Tue Jan  1 07:49:04 2019.
 */

#include <string.h>

#include "uper.h"

struct encoder_t {
    uint8_t *buf_p;
    ssize_t size;
    ssize_t pos;
};

struct decoder_t {
    const uint8_t *buf_p;
    ssize_t size;
    ssize_t pos;
};

static void encoder_init(struct encoder_t *self_p,
                         uint8_t *buf_p,
                         size_t size)
{
    self_p->buf_p = buf_p;
    self_p->size = (8 * size);
    self_p->pos = 0;
}

static ssize_t encoder_get_result(struct encoder_t *self_p)
{
    if (self_p->size >= 0) {
        return ((self_p->pos + 7) / 8);
    } else {
        return (self_p->pos);
    }
}

static void encoder_abort(struct encoder_t *self_p,
                          ssize_t error)
{
    if (self_p->size >= 0) {
        self_p->size = -error;
        self_p->pos = -error;
    }
}

static void encoder_append_bytes(struct encoder_t *self_p,
                                 const uint8_t *buf_p,
                                 size_t size)
{
    encoder_append_bits(self_p, buf_p, 8 * size);
}

static void encoder_append_bool(struct encoder_t *self_p, bool value)
{
    encoder_append_bit(self_p, value ? 1 : 0);
}

static void encoder_append_non_negative_binary_integer(struct encoder_t *self_p,
                                                       uint64_t value,
                                                       size_t size)
{
    size_t i;

    for (i = 0; i < size; i++) {
        encoder_append_bit(self_p, (value >> (size - i - 1)) & 1);
    }
}

static void decoder_init(struct decoder_t *self_p,
                         const uint8_t *buf_p,
                         size_t size)
{
    self_p->buf_p = buf_p;
    self_p->size = (8 * size);
    self_p->pos = 0;
}

static ssize_t decoder_get_result(struct decoder_t *self_p)
{
    if (self_p->size >= 0) {
        return ((self_p->pos + 7) / 8);
    } else {
        return (self_p->pos);
    }
}

static void decoder_abort(struct decoder_t *self_p,
                          ssize_t error)
{
    if (self_p->size >= 0) {
        self_p->size = -error;
        self_p->pos = -error;
    }
}

static void decoder_read_bytes(struct decoder_t *self_p,
                               uint8_t *buf_p,
                               size_t size)
{
    decoder_read_bits(self_p, buf_p, 8 * size);
}

static bool decoder_read_bool(struct decoder_t *self_p)
{
    return (decoder_read_bit(self_p));
}

static uint64_t decoder_read_non_negative_binary_integer(struct decoder_t *self_p,
                                                         size_t size)
{
    size_t i;
    uint64_t value;

    value = 0;

    for (i = 0; i < size; i++) {
        value <<= 1;
        value |= decoder_read_bit(self_p);
    }

    return (value);
}

static void uper_c_source_a_encode_inner(
    struct encoder_t *encoder_p,
    const struct uper_c_source_a_t *src_p)
{
    encoder_append_integer_8(encoder_p, src_p->a);
    encoder_append_integer_16(encoder_p, src_p->b);
    encoder_append_integer_32(encoder_p, src_p->c);
    encoder_append_integer_64(encoder_p, src_p->d);
    encoder_append_integer_8(encoder_p, src_p->e);
    encoder_append_integer_16(encoder_p, src_p->f);
    encoder_append_integer_32(encoder_p, src_p->g);
    encoder_append_integer_64(encoder_p, src_p->h);
    encoder_append_bool(encoder_p, src_p->i);
    encoder_append_bytes(encoder_p,
                         &src_p->j.buf[0],
                         11);
}

static void uper_c_source_a_decode_inner(
    struct decoder_t *decoder_p,
    struct uper_c_source_a_t *dst_p)
{
    dst_p->a = decoder_read_integer_8(decoder_p);
    dst_p->b = decoder_read_integer_16(decoder_p);
    dst_p->c = decoder_read_integer_32(decoder_p);
    dst_p->d = decoder_read_integer_64(decoder_p);
    dst_p->e = decoder_read_integer_8(decoder_p);
    dst_p->f = decoder_read_integer_16(decoder_p);
    dst_p->g = decoder_read_integer_32(decoder_p);
    dst_p->h = decoder_read_integer_64(decoder_p);
    dst_p->i = decoder_read_bool(decoder_p);
    decoder_read_bytes(decoder_p,
                       &dst_p->j.buf[0],
                       11);
}

static void uper_c_source_b_encode_inner(
    struct encoder_t *encoder_p,
    const struct uper_c_source_b_t *src_p)
{
    switch (src_p->choice) {

    case uper_c_source_b_choice_a_e:
        encoder_append_integer_8(encoder_p, 0x00);
        encoder_append_integer_8(encoder_p, src_p->value.a);
        break;

    case uper_c_source_b_choice_b_e:
        encoder_append_integer_8(encoder_p, 0x01);
        uper_c_source_a_encode_inner(encoder_p, &src_p->value.b);
        break;

    case uper_c_source_b_choice_c_e:
        encoder_append_integer_8(encoder_p, 0x02);
        break;

    default:
        encoder_abort(encoder_p, EBADCHOICE);
        break;
    }
}

static void uper_c_source_b_decode_inner(
    struct decoder_t *decoder_p,
    struct uper_c_source_b_t *dst_p)
{
    uint8_t tag;

    tag = decoder_read_integer_8(decoder_p);

    switch (tag) {

    case 0x00:
        dst_p->choice = uper_c_source_b_choice_a_e;
        dst_p->value.a = decoder_read_integer_8(decoder_p);
        break;

    case 0x01:
        dst_p->choice = uper_c_source_b_choice_b_e;
        uper_c_source_a_decode_inner(decoder_p, &dst_p->value.b);
        break;

    case 0x02:
        dst_p->choice = uper_c_source_b_choice_c_e;
        break;

    default:
        decoder_abort(decoder_p, EBADCHOICE);
        break;
    }
}

static void uper_c_source_c_encode_inner(
    struct encoder_t *encoder_p,
    const struct uper_c_source_c_t *src_p)
{
    uint8_t i;

    encoder_append_non_negative_binary_integer(
        encoder_p,
        src_p->length - 0,
        2);

    for (i = 0; i < src_p->length; i++) {
        uper_c_source_b_encode_inner(encoder_p, &src_p->elements[i]);
    }
}

static void uper_c_source_c_decode_inner(
    struct decoder_t *decoder_p,
    struct uper_c_source_c_t *dst_p)
{
    uint8_t i;

    dst_p->length = decoder_read_non_negative_binary_integer(
        decoder_p,
        2);

    if (dst_p->length > 2) {
        decoder_abort(decoder_p, EBADLENGTH);

        return;
    }

    for (i = 0; i < dst_p->length; i++) {
        uper_c_source_b_decode_inner(decoder_p, &dst_p->elements[i]);
    }
}

static void uper_c_source_d_encode_inner(
    struct encoder_t *encoder_p,
    const struct uper_c_source_d_t *src_p)
{
    uint8_t i;
    uint8_t i_2;
    uint8_t present_mask[1];
    uint8_t present_mask_2[1];

    encoder_append_non_negative_binary_integer(
        encoder_p,
        src_p->length - 1,
        4);

    for (i = 0; i < src_p->length; i++) {
        switch (src_p->elements[i].a.b.choice) {

        case uper_c_source_d_a_b_choice_c_e:
            encoder_append_integer_8(encoder_p, 0x00);
            encoder_append_integer_8(encoder_p, src_p->elements[i].a.b.value.c);
            break;

        case uper_c_source_d_a_b_choice_d_e:
            encoder_append_integer_8(encoder_p, 0x01);
            encoder_append_bool(encoder_p, src_p->elements[i].a.b.value.d);
            break;

        default:
            encoder_abort(encoder_p, EBADCHOICE);
            break;
        }

        encoder_append_non_negative_binary_integer(
            encoder_p,
            src_p->elements[i].a.e.length - 3,
            1);

        for (i_2 = 0; i_2 < src_p->elements[i].a.e.length; i_2++) {
        }

        encoder_append_integer_8(encoder_p, src_p->elements[i].g.h);
        encoder_append_integer_8(encoder_p, src_p->elements[i].g.l.length);
        encoder_append_bytes(encoder_p,
                             &src_p->elements[i].g.l.buf[0],
                             src_p->elements[i].g.l.length);
        present_mask[0] = 0;

        if (src_p->elements[i].m.is_n_present) {
            present_mask[0] |= 0x80;
        }

        if (src_p->elements[i].m.o != 3) {
            present_mask[0] |= 0x40;
        }

        if (src_p->elements[i].m.is_p_present) {
            present_mask[0] |= 0x20;
        }

        encoder_append_bytes(encoder_p,
                             &present_mask[0],
                             sizeof(present_mask));

        if (src_p->elements[i].m.is_n_present) {
            encoder_append_bool(encoder_p, src_p->elements[i].m.n);
        }

        if (src_p->elements[i].m.o != 3) {
            encoder_append_integer_8(encoder_p, src_p->elements[i].m.o);
        }

        if (src_p->elements[i].m.is_p_present) {
            present_mask_2[0] = 0;

            if (src_p->elements[i].m.p.is_r_present) {
                present_mask_2[0] |= 0x80;
            }

            encoder_append_bytes(encoder_p,
                                 &present_mask_2[0],
                                 sizeof(present_mask_2));

            encoder_append_bytes(encoder_p,
                                 &src_p->elements[i].m.p.q.buf[0],
                                 5);

            if (src_p->elements[i].m.p.is_r_present) {
                encoder_append_bool(encoder_p, src_p->elements[i].m.p.r);
            }
        }
    }
}

static void uper_c_source_d_decode_inner(
    struct decoder_t *decoder_p,
    struct uper_c_source_d_t *dst_p)
{
    uint8_t i;
    uint8_t tag;
    uint8_t i_2;
    uint8_t present_mask[1];
    uint8_t present_mask_2[1];

    dst_p->length = decoder_read_non_negative_binary_integer(
        decoder_p,
        4);

    if (dst_p->length > 10) {
        decoder_abort(decoder_p, EBADLENGTH);

        return;
    }

    for (i = 0; i < dst_p->length; i++) {
        tag = decoder_read_integer_8(decoder_p);

        switch (tag) {

        case 0x00:
            dst_p->elements[i].a.b.choice = uper_c_source_d_a_b_choice_c_e;
            dst_p->elements[i].a.b.value.c = decoder_read_integer_8(decoder_p);
            break;

        case 0x01:
            dst_p->elements[i].a.b.choice = uper_c_source_d_a_b_choice_d_e;
            dst_p->elements[i].a.b.value.d = decoder_read_bool(decoder_p);
            break;

        default:
            decoder_abort(decoder_p, EBADCHOICE);
            break;
        }

        dst_p->elements[i].a.e.length = decoder_read_non_negative_binary_integer(
            decoder_p,
            1);

        if (dst_p->elements[i].a.e.length > 4) {
            decoder_abort(decoder_p, EBADLENGTH);

            return;
        }

        for (i_2 = 0; i_2 < dst_p->elements[i].a.e.length; i_2++) {
        }

        dst_p->elements[i].g.h = decoder_read_integer_8(decoder_p);
        dst_p->elements[i].g.l.length = decoder_read_integer_8(decoder_p);

        if (dst_p->elements[i].g.l.length > 2) {
            decoder_abort(decoder_p, EBADLENGTH);

            return;
        }

        decoder_read_bytes(decoder_p,
                           &dst_p->elements[i].g.l.buf[0],
                           dst_p->elements[i].g.l.length);
        decoder_read_bytes(decoder_p,
                           &present_mask[0],
                           sizeof(present_mask));

        dst_p->elements[i].m.is_n_present = ((present_mask[0] & 0x80) == 0x80);
        dst_p->elements[i].m.is_p_present = ((present_mask[0] & 0x20) == 0x20);

        if (dst_p->elements[i].m.is_n_present) {
            dst_p->elements[i].m.n = decoder_read_bool(decoder_p);
        }

        if ((present_mask[0] & 0x40) == 0x40) {
            dst_p->elements[i].m.o = decoder_read_integer_8(decoder_p);
        } else {
            dst_p->elements[i].m.o = 3;
        }

        if (dst_p->elements[i].m.is_p_present) {
            decoder_read_bytes(decoder_p,
                               &present_mask_2[0],
                               sizeof(present_mask_2));

            dst_p->elements[i].m.p.is_r_present = ((present_mask_2[0] & 0x80) == 0x80);

            decoder_read_bytes(decoder_p,
                               &dst_p->elements[i].m.p.q.buf[0],
                               5);

            if (dst_p->elements[i].m.p.is_r_present) {
                dst_p->elements[i].m.p.r = decoder_read_bool(decoder_p);
            }
        }
    }
}

static void uper_c_source_e_encode_inner(
    struct encoder_t *encoder_p,
    const struct uper_c_source_e_t *src_p)
{
    switch (src_p->a.choice) {

    case uper_c_source_e_a_choice_b_e:
        encoder_append_integer_8(encoder_p, 0x00);

        switch (src_p->a.value.b.choice) {

        case uper_c_source_e_a_b_choice_c_e:
            encoder_append_integer_8(encoder_p, 0x00);
            encoder_append_bool(encoder_p, src_p->a.value.b.value.c);
            break;

        default:
            encoder_abort(encoder_p, EBADCHOICE);
            break;
        }

        break;

    default:
        encoder_abort(encoder_p, EBADCHOICE);
        break;
    }
}

static void uper_c_source_e_decode_inner(
    struct decoder_t *decoder_p,
    struct uper_c_source_e_t *dst_p)
{
    uint8_t tag;
    uint8_t tag_2;

    tag = decoder_read_integer_8(decoder_p);

    switch (tag) {

    case 0x00:
        dst_p->a.choice = uper_c_source_e_a_choice_b_e;
        tag_2 = decoder_read_integer_8(decoder_p);

        switch (tag_2) {

        case 0x00:
            dst_p->a.value.b.choice = uper_c_source_e_a_b_choice_c_e;
            dst_p->a.value.b.value.c = decoder_read_bool(decoder_p);
            break;

        default:
            decoder_abort(decoder_p, EBADCHOICE);
            break;
        }

        break;

    default:
        decoder_abort(decoder_p, EBADCHOICE);
        break;
    }
}

static void uper_c_source_f_encode_inner(
    struct encoder_t *encoder_p,
    const struct uper_c_source_f_t *src_p)
{
    uint8_t i;
    uint8_t i_2;

    encoder_append_non_negative_binary_integer(
        encoder_p,
        src_p->length - 1,
        1);

    for (i = 0; i < src_p->length; i++) {
        encoder_append_integer_8(encoder_p, 1);
        encoder_append_integer_8(encoder_p, 1);

        for (i_2 = 0; i_2 < 1; i_2++) {
            encoder_append_bool(encoder_p, src_p->elements[i].elements[i_2]);
        }
    }
}

static void uper_c_source_f_decode_inner(
    struct decoder_t *decoder_p,
    struct uper_c_source_f_t *dst_p)
{
    uint8_t i;
    uint8_t i_2;
    uint8_t length;

    dst_p->length = decoder_read_non_negative_binary_integer(
        decoder_p,
        1);

    if (dst_p->length > 2) {
        decoder_abort(decoder_p, EBADLENGTH);

        return;
    }

    for (i = 0; i < dst_p->length; i++) {
        length = decoder_read_integer_8(decoder_p);

        if (length > 1) {
            decoder_abort(decoder_p, EBADLENGTH);

            return;
        }

        for (i_2 = 0; i_2 < 1; i_2++) {
            dst_p->elements[i].elements[i_2] = decoder_read_bool(decoder_p);
        }
    }
}

static void uper_c_source_g_encode_inner(
    struct encoder_t *encoder_p,
    const struct uper_c_source_g_t *src_p)
{
    uint8_t present_mask[2];

    present_mask[0] = 0;
    present_mask[1] = 0;

    if (src_p->is_a_present) {
        present_mask[0] |= 0x80;
    }

    if (src_p->is_b_present) {
        present_mask[0] |= 0x40;
    }

    if (src_p->is_c_present) {
        present_mask[0] |= 0x20;
    }

    if (src_p->is_d_present) {
        present_mask[0] |= 0x10;
    }

    if (src_p->is_e_present) {
        present_mask[0] |= 0x08;
    }

    if (src_p->is_f_present) {
        present_mask[0] |= 0x04;
    }

    if (src_p->is_g_present) {
        present_mask[0] |= 0x02;
    }

    if (src_p->is_h_present) {
        present_mask[0] |= 0x01;
    }

    if (src_p->is_i_present) {
        present_mask[1] |= 0x80;
    }

    encoder_append_bytes(encoder_p,
                         &present_mask[0],
                         sizeof(present_mask));

    if (src_p->is_a_present) {
        encoder_append_bool(encoder_p, src_p->a);
    }

    if (src_p->is_b_present) {
        encoder_append_bool(encoder_p, src_p->b);
    }

    if (src_p->is_c_present) {
        encoder_append_bool(encoder_p, src_p->c);
    }

    if (src_p->is_d_present) {
        encoder_append_bool(encoder_p, src_p->d);
    }

    if (src_p->is_e_present) {
        encoder_append_bool(encoder_p, src_p->e);
    }

    if (src_p->is_f_present) {
        encoder_append_bool(encoder_p, src_p->f);
    }

    if (src_p->is_g_present) {
        encoder_append_bool(encoder_p, src_p->g);
    }

    if (src_p->is_h_present) {
        encoder_append_bool(encoder_p, src_p->h);
    }

    if (src_p->is_i_present) {
        encoder_append_bool(encoder_p, src_p->i);
    }
}

static void uper_c_source_g_decode_inner(
    struct decoder_t *decoder_p,
    struct uper_c_source_g_t *dst_p)
{
    uint8_t present_mask[2];

    decoder_read_bytes(decoder_p,
                       &present_mask[0],
                       sizeof(present_mask));

    dst_p->is_a_present = ((present_mask[0] & 0x80) == 0x80);
    dst_p->is_b_present = ((present_mask[0] & 0x40) == 0x40);
    dst_p->is_c_present = ((present_mask[0] & 0x20) == 0x20);
    dst_p->is_d_present = ((present_mask[0] & 0x10) == 0x10);
    dst_p->is_e_present = ((present_mask[0] & 0x08) == 0x08);
    dst_p->is_f_present = ((present_mask[0] & 0x04) == 0x04);
    dst_p->is_g_present = ((present_mask[0] & 0x02) == 0x02);
    dst_p->is_h_present = ((present_mask[0] & 0x01) == 0x01);
    dst_p->is_i_present = ((present_mask[1] & 0x80) == 0x80);

    if (dst_p->is_a_present) {
        dst_p->a = decoder_read_bool(decoder_p);
    }

    if (dst_p->is_b_present) {
        dst_p->b = decoder_read_bool(decoder_p);
    }

    if (dst_p->is_c_present) {
        dst_p->c = decoder_read_bool(decoder_p);
    }

    if (dst_p->is_d_present) {
        dst_p->d = decoder_read_bool(decoder_p);
    }

    if (dst_p->is_e_present) {
        dst_p->e = decoder_read_bool(decoder_p);
    }

    if (dst_p->is_f_present) {
        dst_p->f = decoder_read_bool(decoder_p);
    }

    if (dst_p->is_g_present) {
        dst_p->g = decoder_read_bool(decoder_p);
    }

    if (dst_p->is_h_present) {
        dst_p->h = decoder_read_bool(decoder_p);
    }

    if (dst_p->is_i_present) {
        dst_p->i = decoder_read_bool(decoder_p);
    }
}

static void uper_c_source_h_encode_inner(
    struct encoder_t *encoder_p,
    const struct uper_c_source_h_t *src_p)
{
    (void)encoder_p;
    (void)src_p;
}

static void uper_c_source_h_decode_inner(
    struct decoder_t *decoder_p,
    struct uper_c_source_h_t *dst_p)
{
    (void)decoder_p;
    (void)dst_p;
}

static void uper_c_source_i_encode_inner(
    struct encoder_t *encoder_p,
    const struct uper_c_source_i_t *src_p)
{
    encoder_append_bytes(encoder_p,
                         &src_p->buf[0],
                         24);
}

static void uper_c_source_i_decode_inner(
    struct decoder_t *decoder_p,
    struct uper_c_source_i_t *dst_p)
{
    decoder_read_bytes(decoder_p,
                       &dst_p->buf[0],
                       24);
}

static void uper_c_source_j_encode_inner(
    struct encoder_t *encoder_p,
    const struct uper_c_source_j_t *src_p)
{
    encoder_append_integer_8(encoder_p, src_p->length);
    encoder_append_bytes(encoder_p,
                         &src_p->buf[0],
                         src_p->length);
}

static void uper_c_source_j_decode_inner(
    struct decoder_t *decoder_p,
    struct uper_c_source_j_t *dst_p)
{
    dst_p->length = decoder_read_integer_8(decoder_p);

    if (dst_p->length > 23) {
        decoder_abort(decoder_p, EBADLENGTH);

        return;
    }

    decoder_read_bytes(decoder_p,
                       &dst_p->buf[0],
                       dst_p->length);
}

static void uper_c_source_k_encode_inner(
    struct encoder_t *encoder_p,
    const struct uper_c_source_k_t *src_p)
{
    encoder_append_integer_8(encoder_p, src_p->value);
}

static void uper_c_source_k_decode_inner(
    struct decoder_t *decoder_p,
    struct uper_c_source_k_t *dst_p)
{
    dst_p->value = decoder_read_integer_8(decoder_p);
}

static void uper_c_source_l_encode_inner(
    struct encoder_t *encoder_p,
    const struct uper_c_source_l_t *src_p)
{
    encoder_append_length_determinant(encoder_p, src_p->length);
    encoder_append_bytes(encoder_p,
                         &src_p->buf[0],
                         src_p->length);
}

static void uper_c_source_l_decode_inner(
    struct decoder_t *decoder_p,
    struct uper_c_source_l_t *dst_p)
{
    dst_p->length = decoder_read_length_determinant(decoder_p);

    if (dst_p->length > 500) {
        decoder_abort(decoder_p, EBADLENGTH);

        return;
    }

    decoder_read_bytes(decoder_p,
                       &dst_p->buf[0],
                       dst_p->length);
}

static void uper_c_source_o_encode_inner(
    struct encoder_t *encoder_p,
    const struct uper_c_source_o_t *src_p)
{
    uint16_t i;

    encoder_append_non_negative_binary_integer(
        encoder_p,
        src_p->length - 1,
        9);

    for (i = 0; i < src_p->length; i++) {
        encoder_append_bool(encoder_p, src_p->elements[i]);
    }
}

static void uper_c_source_o_decode_inner(
    struct decoder_t *decoder_p,
    struct uper_c_source_o_t *dst_p)
{
    uint16_t i;

    dst_p->length = decoder_read_non_negative_binary_integer(
        decoder_p,
        9);

    if (dst_p->length > 260) {
        decoder_abort(decoder_p, EBADLENGTH);

        return;
    }

    for (i = 0; i < dst_p->length; i++) {
        dst_p->elements[i] = decoder_read_bool(decoder_p);
    }
}

static void uper_c_source_n_encode_inner(
    struct encoder_t *encoder_p,
    const struct uper_c_source_n_t *src_p)
{
    uper_c_source_k_encode_inner(encoder_p, &src_p->a);
    uper_c_source_a_encode_inner(encoder_p, &src_p->b);
    uper_c_source_o_encode_inner(encoder_p, &src_p->c);
}

static void uper_c_source_n_decode_inner(
    struct decoder_t *decoder_p,
    struct uper_c_source_n_t *dst_p)
{
    uper_c_source_k_decode_inner(decoder_p, &dst_p->a);
    uper_c_source_a_decode_inner(decoder_p, &dst_p->b);
    uper_c_source_o_decode_inner(decoder_p, &dst_p->c);
}

static void uper_c_source_m_encode_inner(
    struct encoder_t *encoder_p,
    const struct uper_c_source_m_t *src_p)
{
    uper_c_source_k_encode_inner(encoder_p, &src_p->a);
    uper_c_source_n_encode_inner(encoder_p, &src_p->b);
}

static void uper_c_source_m_decode_inner(
    struct decoder_t *decoder_p,
    struct uper_c_source_m_t *dst_p)
{
    uper_c_source_k_decode_inner(decoder_p, &dst_p->a);
    uper_c_source_n_decode_inner(decoder_p, &dst_p->b);
}

static void uper_c_source_p_encode_inner(
    struct encoder_t *encoder_p,
    const struct uper_c_source_p_t *src_p)
{
    uper_c_source_a_encode_inner(encoder_p, &src_p->a);
    uper_c_source_m_encode_inner(encoder_p, &src_p->b);
    uper_c_source_f_encode_inner(encoder_p, &src_p->c);
}

static void uper_c_source_p_decode_inner(
    struct decoder_t *decoder_p,
    struct uper_c_source_p_t *dst_p)
{
    uper_c_source_a_decode_inner(decoder_p, &dst_p->a);
    uper_c_source_m_decode_inner(decoder_p, &dst_p->b);
    uper_c_source_f_decode_inner(decoder_p, &dst_p->c);
}

ssize_t uper_c_source_a_encode(
    uint8_t *dst_p,
    size_t size,
    const struct uper_c_source_a_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    uper_c_source_a_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t uper_c_source_a_decode(
    struct uper_c_source_a_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    uper_c_source_a_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t uper_c_source_b_encode(
    uint8_t *dst_p,
    size_t size,
    const struct uper_c_source_b_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    uper_c_source_b_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t uper_c_source_b_decode(
    struct uper_c_source_b_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    uper_c_source_b_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t uper_c_source_c_encode(
    uint8_t *dst_p,
    size_t size,
    const struct uper_c_source_c_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    uper_c_source_c_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t uper_c_source_c_decode(
    struct uper_c_source_c_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    uper_c_source_c_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t uper_c_source_d_encode(
    uint8_t *dst_p,
    size_t size,
    const struct uper_c_source_d_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    uper_c_source_d_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t uper_c_source_d_decode(
    struct uper_c_source_d_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    uper_c_source_d_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t uper_c_source_e_encode(
    uint8_t *dst_p,
    size_t size,
    const struct uper_c_source_e_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    uper_c_source_e_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t uper_c_source_e_decode(
    struct uper_c_source_e_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    uper_c_source_e_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t uper_c_source_f_encode(
    uint8_t *dst_p,
    size_t size,
    const struct uper_c_source_f_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    uper_c_source_f_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t uper_c_source_f_decode(
    struct uper_c_source_f_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    uper_c_source_f_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t uper_c_source_g_encode(
    uint8_t *dst_p,
    size_t size,
    const struct uper_c_source_g_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    uper_c_source_g_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t uper_c_source_g_decode(
    struct uper_c_source_g_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    uper_c_source_g_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t uper_c_source_h_encode(
    uint8_t *dst_p,
    size_t size,
    const struct uper_c_source_h_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    uper_c_source_h_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t uper_c_source_h_decode(
    struct uper_c_source_h_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    uper_c_source_h_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t uper_c_source_i_encode(
    uint8_t *dst_p,
    size_t size,
    const struct uper_c_source_i_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    uper_c_source_i_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t uper_c_source_i_decode(
    struct uper_c_source_i_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    uper_c_source_i_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t uper_c_source_j_encode(
    uint8_t *dst_p,
    size_t size,
    const struct uper_c_source_j_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    uper_c_source_j_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t uper_c_source_j_decode(
    struct uper_c_source_j_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    uper_c_source_j_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t uper_c_source_k_encode(
    uint8_t *dst_p,
    size_t size,
    const struct uper_c_source_k_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    uper_c_source_k_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t uper_c_source_k_decode(
    struct uper_c_source_k_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    uper_c_source_k_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t uper_c_source_l_encode(
    uint8_t *dst_p,
    size_t size,
    const struct uper_c_source_l_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    uper_c_source_l_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t uper_c_source_l_decode(
    struct uper_c_source_l_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    uper_c_source_l_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t uper_c_source_o_encode(
    uint8_t *dst_p,
    size_t size,
    const struct uper_c_source_o_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    uper_c_source_o_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t uper_c_source_o_decode(
    struct uper_c_source_o_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    uper_c_source_o_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t uper_c_source_n_encode(
    uint8_t *dst_p,
    size_t size,
    const struct uper_c_source_n_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    uper_c_source_n_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t uper_c_source_n_decode(
    struct uper_c_source_n_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    uper_c_source_n_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t uper_c_source_m_encode(
    uint8_t *dst_p,
    size_t size,
    const struct uper_c_source_m_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    uper_c_source_m_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t uper_c_source_m_decode(
    struct uper_c_source_m_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    uper_c_source_m_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t uper_c_source_p_encode(
    uint8_t *dst_p,
    size_t size,
    const struct uper_c_source_p_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    uper_c_source_p_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t uper_c_source_p_decode(
    struct uper_c_source_p_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    uper_c_source_p_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}
