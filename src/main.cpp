#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <stdexcept>

namespace py = pybind11;

py::array_t<uint8_t> rgb_to_gray(py::array_t<uint8_t> input) {
    py::buffer_info buf = input.request();

    if (buf.ndim != 3) {
        throw std::runtime_error("Input must be a 3D array (Height, Width, Channels)");
    }
    if (buf.shape[2] != 3) {
        throw std::runtime_error("Last dimension must be 3 (RGB channels)");
    }
    
    size_t height = buf.shape[0];
    size_t width = buf.shape[1];

    auto result = py::array_t<uint8_t>({height, width});
    py::buffer_info res_buf = result.request();

    uint8_t* ptr_in = static_cast<uint8_t*>(buf.ptr);
    uint8_t* ptr_out = static_cast<uint8_t*>(res_buf.ptr);

    size_t stride_h_in = buf.strides[0];
    size_t stride_w_in = buf.strides[1];
    size_t stride_c_in = buf.strides[2];
    
    size_t stride_h_out = res_buf.strides[0];
    size_t stride_w_out = res_buf.strides[1];

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            uint8_t* pixel = ptr_in + y * stride_h_in + x * stride_w_in;
            uint8_t r = pixel[0 * stride_c_in];
            uint8_t g = pixel[1 * stride_c_in];
            uint8_t b = pixel[2 * stride_c_in];

            uint8_t gray = static_cast<uint8_t>(0.299f * r + 0.587f * g + 0.114f * b);

            uint8_t* out_pixel = ptr_out + y * stride_h_out + x * stride_w_out;
            *out_pixel = gray;
        }
    }

    return result;
}

PYBIND11_MODULE(_core, m) {
    m.doc() = "C++ bindings for image processing";
    m.def("rgb_to_gray", &rgb_to_gray, "Convert RGB image to Grayscale",
          py::arg("input"));
}
