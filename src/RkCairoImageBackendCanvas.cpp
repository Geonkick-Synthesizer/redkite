
#include "RkCairoImageBackendCanvas.h"
#include "RkCanvasInfo.h"

RkCairoImageBackendCanvas::RkCairoImageBackendCanvas(const std::pair<int, int> &size,
                                                     RkImage::Format format,
                                                     const unsigned char *data)
        : canvasInfo{nullptr}
        , imageSize{size}
{
#ifdef RK_OS_WIN
#elif RK_OS_MAC
#else // X11
        auto cairoFormat = toCairoFormat(format);
        if (cairoFormat != CAIRO_FORMAT_INVALID && imageSize.first != 0 && imageSize.second != 0) {
                canvasInfo = std::make_shared<RkCanvasInfo>();
                auto stride = cairo_format_stride_for_width(cairoFormat, imageSize.first);
                imageData.assign(data, data + imageSize.first * imageSize.second * pixelLength(format));
                canvasInfo->cairo_surface = cairo_image_surface_create_for_data(imageData.data(),
                                                                                CAIRO_FORMAT_ARGB32,
                                                                                imageSize.first,
                                                                                imageSize.second,
                                                                                stride);
        }
#endif
}

RkCairoImageBackendCanvas::~RkCairoImageBackendCanvas()
{
        if (canvasInfo)
                cairo_surface_destroy(canvasInfo->cairo_surface);
}

cairo_format_t RkCairoImageBackendCanvas::toCairoFormat(RkImage::Format format) const
{
        switch (format)
        {
        case RkImage::Format::ARGB32: return CAIRO_FORMAT_ARGB32;
        case RkImage::Format::RGB32:  return CAIRO_FORMAT_RGB24;
        default: return CAIRO_FORMAT_INVALID;
        }
}

int RkCairoImageBackendCanvas::pixelLength(RkImage::Format format) const
{
        switch (format)
        {
        case RkImage::Format::ARGB32:
        case RkImage::Format::RGB32:  return 4;
        default: return 1;
        }
}

std::pair<int, int> RkCairoImageBackendCanvas::size() const
{
        return imageSize;
}

bool RkCairoImageBackendCanvas::isNull() const
{
        return canvasInfo == nullptr;
}

const unsigned char* RkCairoImageBackendCanvas::data() const
{
        return imageData.data();
}

std::vector<unsigned char> RkCairoImageBackendCanvas::dataCopy() const
{
        return imageData;
}

std::shared_ptr<RkCanvasInfo> RkCairoImageBackendCanvas::getCanvasInfo() const
{
        return canvasInfo;
}
