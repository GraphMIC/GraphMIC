#include "gmImageConvert.hpp"

#include "gmLog.hpp"
#include "gmImageAttributes.hpp"

namespace gm
{
    namespace Image
    {
        auto ToCv(Data::Image* image) -> cv::Mat
        {
            if (!image)
            {
                return cv::Mat();
            }

            auto attributes = image->getAttributes();

            if (attributes->getPixelID() == Pixel::ID::Rgba)
            {
                throw new std::runtime_error("RGBA pixel type image can not be converted to cvMat");
            }

            mitk::ImageToOpenCVImageFilter::Pointer converter = mitk::ImageToOpenCVImageFilter::New();

            auto mitkImage = image->getMitkImage();

            converter->SetImage(mitkImage);

            auto mat = converter->GetOpenCVMat();

            if (mat.empty())
            {
                throw new std::runtime_error("unable to convert image to cvMat");
            }

            return converter->GetOpenCVMat();
        }

        auto FromCv(cv::Mat cvMat) -> Data::Image*
        {
            if (cvMat.empty())
            {
                log_error("cvMat is empty, can not convert to CoreImage!");
                return nullptr;
            }

            mitk::OpenCVToMitkImageFilter::Pointer converter = mitk::OpenCVToMitkImageFilter::New();

            converter->SetOpenCVMat(cvMat);
            converter->Update();

            auto output = converter->GetOutput();

            if (!output)
            {
                log_error("Converting image data from cvMat to CoreImage failed!");
                return nullptr;
            }

            return new Data::Image(converter->GetOutput());
        }
    }
}
