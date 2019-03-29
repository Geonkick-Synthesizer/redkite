
#include "RkCairoImageBackendCanvas.h"
#include "RkCanvasInfo.h"

RkImageBackendCanvas::RkImageBackendCanvas(const std::pair<int, int> &size, RkImage::Format format, const unsigend char *data)
        : canvasInfo{nullptr}
        , imageSize{size}
{
#ifdef RK_OS_WIN
#elif RK_OS_MAC
#else // X11
        auto cairoFormat = toCairoFormat(format);
        if (cairoFormat != CAIRO_FORMAT_INVALID) {
                canvasInfo = std::make_shared<RkCanvasInfo>();
                auto stride = cairo_format_stride_for_width(cairoFormat, imageSize.width());
                imageData.assign(data, data + imageSize.fist * imageSize.second * pixelLength());
                canvasInfo->cairo_surface_t = cairo_image_surface_create_for_data(imageData.data(),
                                                                                  CAIRO_FORMAT_ARGB32,
                                                                                  imageSize.first,
                                                                                  imageSize.second,
                                                                                  stride);
        }
#endif;
}

RkImageBackendCanvas::~RkImageBackendCanvas()
{
}

std::pair<int, int> RkImageBackendCanvas::size() const
{
        return imageSize;
}

RkImage::Format RkImageBackendCanvas::format() const
{
        return fromFairoFromat(imageFormat);
}

bool RkImageBackendCanvas::isNull() const
{
        return canvasInfo == nullptr;
}

const unsigned char* RkImageBackendCanvas::data() const
{
        return imageData.data();
}

std::vector<unsigned char> RkImageBackendCanvas::dataCopy() const
{
        return imageData;
}

std::shared_ptr<RkCanvasInfo> RkImageBackendCanvas::getCanvasInfo() const
{
        return canvasInfo;
}
