#ifndef INCUBATOR_USBCOMMANDHANDLER_H
#define INCUBATOR_USBCOMMANDHANDLER_H
namespace Incubator
{
class UsbCommandHandler
{
public:
  UsbCommandHandler()  = default;
  ~UsbCommandHandler() = default;
  auto Run(void) -> void;
};
} // namespace Incubator
#endif // INCUBATOR_USBCOMMANDHANDLER_H
