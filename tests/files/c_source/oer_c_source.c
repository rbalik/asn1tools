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
 * This file was generated by asn1tools version 0.138.2 Thu Dec 27 15:43:15 2018.
 */

#include <string.h>

#include "oer_c_source.h"

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
    self_p->size = size;
    self_p->pos = 0;
}

static ssize_t encoder_get_result(struct encoder_t *self_p)
{
    return (self_p->pos);
}

static void encoder_abort(struct encoder_t *self_p,
                          ssize_t error)
{
    if (self_p->size >= 0) {
        self_p->size = -error;
        self_p->pos = -error;
    }
}

static size_t encoder_alloc(struct encoder_t *self_p,
                            size_t size)
{
    ssize_t pos;

    if (self_p->pos + (ssize_t)size <= self_p->size) {
        pos = self_p->pos;
        self_p->pos += size;
    } else {
        pos = -ENOMEM;
        encoder_abort(self_p, ENOMEM);
    }

    return (pos);
}

static void encoder_append_bytes(struct encoder_t *self_p,
                                 const uint8_t *buf_p,
                                 size_t size)
{
    ssize_t pos;

    pos = encoder_alloc(self_p, size);

    if (pos < 0) {
        return;
    }

    memcpy(&self_p->buf_p[pos], buf_p, size);
}

static void encoder_append_integer_8(struct encoder_t *self_p,
                                     uint8_t value)
{
    encoder_append_bytes(self_p, &value, sizeof(value));
}

static void encoder_append_integer_16(struct encoder_t *self_p,
                                      uint16_t value)
{
    uint8_t buf[2];

    buf[0] = (value >> 8);
    buf[1] = value;

    encoder_append_bytes(self_p, &buf[0], sizeof(buf));
}

static void encoder_append_integer_32(struct encoder_t *self_p,
                                      uint32_t value)
{
    uint8_t buf[4];

    buf[0] = (value >> 24);
    buf[1] = (value >> 16);
    buf[2] = (value >> 8);
    buf[3] = value;

    encoder_append_bytes(self_p, &buf[0], sizeof(buf));
}

static void encoder_append_integer_64(struct encoder_t *self_p,
                                      uint64_t value)
{
    uint8_t buf[8];

    buf[0] = (value >> 56);
    buf[1] = (value >> 48);
    buf[2] = (value >> 40);
    buf[3] = (value >> 32);
    buf[4] = (value >> 24);
    buf[5] = (value >> 16);
    buf[6] = (value >> 8);
    buf[7] = value;

    encoder_append_bytes(self_p, &buf[0], sizeof(buf));
}

static void encoder_append_float(struct encoder_t *self_p,
                                 float value)
{
    uint32_t i32;

    memcpy(&i32, &value, sizeof(i32));

    encoder_append_integer_32(self_p, i32);
}

static void encoder_append_double(struct encoder_t *self_p,
                                  double value)
{
    uint64_t i64;

    memcpy(&i64, &value, sizeof(i64));

    encoder_append_integer_64(self_p, i64);
}

static void encoder_append_bool(struct encoder_t *self_p, bool value)
{
    encoder_append_integer_8(self_p, value ? 255 : 0);
}

static void decoder_init(struct decoder_t *self_p,
                         const uint8_t *buf_p,
                         size_t size)
{
    self_p->buf_p = buf_p;
    self_p->size = size;
    self_p->pos = 0;
}

static ssize_t decoder_get_result(struct decoder_t *self_p)
{
    return (self_p->pos);
}

static void decoder_abort(struct decoder_t *self_p,
                          ssize_t error)
{
    if (self_p->size >= 0) {
        self_p->size = -error;
        self_p->pos = -error;
    }
}

static size_t decoder_free(struct decoder_t *self_p,
                           size_t size)
{
    ssize_t pos;

    if (self_p->pos + (ssize_t)size <= self_p->size) {
        pos = self_p->pos;
        self_p->pos += size;
    } else {
        pos = -EOUTOFDATA;
        decoder_abort(self_p, EOUTOFDATA);
    }

    return (pos);
}

static void decoder_read_bytes(struct decoder_t *self_p,
                               uint8_t *buf_p,
                               size_t size)
{
    ssize_t pos;

    pos = decoder_free(self_p, size);

    if (pos >= 0) {
        memcpy(buf_p, &self_p->buf_p[pos], size);
    } else {
        memset(buf_p, 0, size);
    }

}

static uint8_t decoder_read_integer_8(struct decoder_t *self_p)
{
    uint8_t value;

    decoder_read_bytes(self_p, &value, sizeof(value));

    return (value);
}

static uint16_t decoder_read_integer_16(struct decoder_t *self_p)
{
    uint8_t buf[2];

    decoder_read_bytes(self_p, &buf[0], sizeof(buf));

    return ((buf[0] << 8) | buf[1]);
}

static uint32_t decoder_read_integer_32(struct decoder_t *self_p)
{
    uint8_t buf[4];

    decoder_read_bytes(self_p, &buf[0], sizeof(buf));

    return ((buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3]);
}

static uint64_t decoder_read_integer_64(struct decoder_t *self_p)
{
    uint8_t buf[8];

    decoder_read_bytes(self_p, &buf[0], sizeof(buf));

    return (((uint64_t)buf[0] << 56)
            | ((uint64_t)buf[1] << 48)
            | ((uint64_t)buf[2] << 40)
            | ((uint64_t)buf[3] << 32)
            | ((uint64_t)buf[4] << 24)
            | ((uint64_t)buf[5] << 16)
            | ((uint64_t)buf[6] << 8)
            | (uint64_t)buf[7]);
}

static float decoder_read_float(struct decoder_t *self_p)
{
    float value;
    uint32_t i32;

    i32 = decoder_read_integer_32(self_p);

    memcpy(&value, &i32, sizeof(value));

    return (value);
}

static double decoder_read_double(struct decoder_t *self_p)
{
    double value;
    uint64_t i64;

    i64 = decoder_read_integer_64(self_p);

    memcpy(&value, &i64, sizeof(value));

    return (value);
}

static bool decoder_read_bool(struct decoder_t *self_p)
{
    uint8_t value;

    value = decoder_read_integer_8(self_p);

    return (value != 0);
}

static void oer_c_source_a_encode_inner(
    struct encoder_t *encoder_p,
    const struct oer_c_source_a_t *src_p)
{
}

static void oer_c_source_a_decode_inner(
    struct decoder_t *decoder_p,
    struct oer_c_source_a_t *dst_p)
{
}

static void oer_c_source_b_encode_inner(
    struct encoder_t *encoder_p,
    const struct oer_c_source_b_t *src_p)
{
}

static void oer_c_source_b_decode_inner(
    struct decoder_t *decoder_p,
    struct oer_c_source_b_t *dst_p)
{
}

static void oer_c_source_c_encode_inner(
    struct encoder_t *encoder_p,
    const struct oer_c_source_c_t *src_p)
{
}

static void oer_c_source_c_decode_inner(
    struct decoder_t *decoder_p,
    struct oer_c_source_c_t *dst_p)
{
}

static void oer_c_source_d_encode_inner(
    struct encoder_t *encoder_p,
    const struct oer_c_source_d_t *src_p)
{
}

static void oer_c_source_d_decode_inner(
    struct decoder_t *decoder_p,
    struct oer_c_source_d_t *dst_p)
{
}

static void oer_programming_types_bool_encode_inner(
    struct encoder_t *encoder_p,
    const struct oer_programming_types_bool_t *src_p)
{
}

static void oer_programming_types_bool_decode_inner(
    struct decoder_t *decoder_p,
    struct oer_programming_types_bool_t *dst_p)
{
}

static void oer_programming_types_double_encode_inner(
    struct encoder_t *encoder_p,
    const struct oer_programming_types_double_t *src_p)
{
}

static void oer_programming_types_double_decode_inner(
    struct decoder_t *decoder_p,
    struct oer_programming_types_double_t *dst_p)
{
}

static void oer_programming_types_float_encode_inner(
    struct encoder_t *encoder_p,
    const struct oer_programming_types_float_t *src_p)
{
}

static void oer_programming_types_float_decode_inner(
    struct decoder_t *decoder_p,
    struct oer_programming_types_float_t *dst_p)
{
}

static void oer_programming_types_int16_encode_inner(
    struct encoder_t *encoder_p,
    const struct oer_programming_types_int16_t *src_p)
{
}

static void oer_programming_types_int16_decode_inner(
    struct decoder_t *decoder_p,
    struct oer_programming_types_int16_t *dst_p)
{
}

static void oer_programming_types_int32_encode_inner(
    struct encoder_t *encoder_p,
    const struct oer_programming_types_int32_t *src_p)
{
}

static void oer_programming_types_int32_decode_inner(
    struct decoder_t *decoder_p,
    struct oer_programming_types_int32_t *dst_p)
{
}

static void oer_programming_types_int64_encode_inner(
    struct encoder_t *encoder_p,
    const struct oer_programming_types_int64_t *src_p)
{
}

static void oer_programming_types_int64_decode_inner(
    struct decoder_t *decoder_p,
    struct oer_programming_types_int64_t *dst_p)
{
}

static void oer_programming_types_int8_encode_inner(
    struct encoder_t *encoder_p,
    const struct oer_programming_types_int8_t *src_p)
{
}

static void oer_programming_types_int8_decode_inner(
    struct decoder_t *decoder_p,
    struct oer_programming_types_int8_t *dst_p)
{
}

static void oer_programming_types_uint16_encode_inner(
    struct encoder_t *encoder_p,
    const struct oer_programming_types_uint16_t *src_p)
{
}

static void oer_programming_types_uint16_decode_inner(
    struct decoder_t *decoder_p,
    struct oer_programming_types_uint16_t *dst_p)
{
}

static void oer_programming_types_uint32_encode_inner(
    struct encoder_t *encoder_p,
    const struct oer_programming_types_uint32_t *src_p)
{
}

static void oer_programming_types_uint32_decode_inner(
    struct decoder_t *decoder_p,
    struct oer_programming_types_uint32_t *dst_p)
{
}

static void oer_programming_types_uint64_encode_inner(
    struct encoder_t *encoder_p,
    const struct oer_programming_types_uint64_t *src_p)
{
}

static void oer_programming_types_uint64_decode_inner(
    struct decoder_t *decoder_p,
    struct oer_programming_types_uint64_t *dst_p)
{
}

static void oer_programming_types_uint8_encode_inner(
    struct encoder_t *encoder_p,
    const struct oer_programming_types_uint8_t *src_p)
{
}

static void oer_programming_types_uint8_decode_inner(
    struct decoder_t *decoder_p,
    struct oer_programming_types_uint8_t *dst_p)
{
}

ssize_t oer_c_source_a_encode(
    uint8_t *dst_p,
    size_t size,
    const struct oer_c_source_a_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    oer_c_source_a_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t oer_c_source_a_decode(
    struct oer_c_source_a_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    oer_c_source_a_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t oer_c_source_b_encode(
    uint8_t *dst_p,
    size_t size,
    const struct oer_c_source_b_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    oer_c_source_b_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t oer_c_source_b_decode(
    struct oer_c_source_b_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    oer_c_source_b_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t oer_c_source_c_encode(
    uint8_t *dst_p,
    size_t size,
    const struct oer_c_source_c_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    oer_c_source_c_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t oer_c_source_c_decode(
    struct oer_c_source_c_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    oer_c_source_c_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t oer_c_source_d_encode(
    uint8_t *dst_p,
    size_t size,
    const struct oer_c_source_d_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    oer_c_source_d_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t oer_c_source_d_decode(
    struct oer_c_source_d_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    oer_c_source_d_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t oer_programming_types_bool_encode(
    uint8_t *dst_p,
    size_t size,
    const struct oer_programming_types_bool_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    oer_programming_types_bool_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t oer_programming_types_bool_decode(
    struct oer_programming_types_bool_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    oer_programming_types_bool_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t oer_programming_types_double_encode(
    uint8_t *dst_p,
    size_t size,
    const struct oer_programming_types_double_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    oer_programming_types_double_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t oer_programming_types_double_decode(
    struct oer_programming_types_double_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    oer_programming_types_double_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t oer_programming_types_float_encode(
    uint8_t *dst_p,
    size_t size,
    const struct oer_programming_types_float_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    oer_programming_types_float_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t oer_programming_types_float_decode(
    struct oer_programming_types_float_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    oer_programming_types_float_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t oer_programming_types_int16_encode(
    uint8_t *dst_p,
    size_t size,
    const struct oer_programming_types_int16_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    oer_programming_types_int16_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t oer_programming_types_int16_decode(
    struct oer_programming_types_int16_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    oer_programming_types_int16_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t oer_programming_types_int32_encode(
    uint8_t *dst_p,
    size_t size,
    const struct oer_programming_types_int32_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    oer_programming_types_int32_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t oer_programming_types_int32_decode(
    struct oer_programming_types_int32_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    oer_programming_types_int32_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t oer_programming_types_int64_encode(
    uint8_t *dst_p,
    size_t size,
    const struct oer_programming_types_int64_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    oer_programming_types_int64_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t oer_programming_types_int64_decode(
    struct oer_programming_types_int64_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    oer_programming_types_int64_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t oer_programming_types_int8_encode(
    uint8_t *dst_p,
    size_t size,
    const struct oer_programming_types_int8_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    oer_programming_types_int8_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t oer_programming_types_int8_decode(
    struct oer_programming_types_int8_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    oer_programming_types_int8_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t oer_programming_types_uint16_encode(
    uint8_t *dst_p,
    size_t size,
    const struct oer_programming_types_uint16_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    oer_programming_types_uint16_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t oer_programming_types_uint16_decode(
    struct oer_programming_types_uint16_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    oer_programming_types_uint16_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t oer_programming_types_uint32_encode(
    uint8_t *dst_p,
    size_t size,
    const struct oer_programming_types_uint32_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    oer_programming_types_uint32_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t oer_programming_types_uint32_decode(
    struct oer_programming_types_uint32_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    oer_programming_types_uint32_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t oer_programming_types_uint64_encode(
    uint8_t *dst_p,
    size_t size,
    const struct oer_programming_types_uint64_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    oer_programming_types_uint64_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t oer_programming_types_uint64_decode(
    struct oer_programming_types_uint64_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    oer_programming_types_uint64_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}

ssize_t oer_programming_types_uint8_encode(
    uint8_t *dst_p,
    size_t size,
    const struct oer_programming_types_uint8_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    oer_programming_types_uint8_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t oer_programming_types_uint8_decode(
    struct oer_programming_types_uint8_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    oer_programming_types_uint8_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}
