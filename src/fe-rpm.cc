#include "globals.h"
#include "flags.h"
#include "usb.h"
#include "dataspec.h"
#include "protocol.h"

static FlagGroup flags;

static DataSpecFlag source(
    { "--source", "-s" },
    "source for data",
    ":d=0:t=0:s=0");

int mainRpm(int argc, const char* argv[])
{
    flags.parseFlags(argc, argv);

    FluxSpec spec(source);
    usbSetDrive(spec.drive, false, F_INDEX_REAL);
    nanoseconds_t period = usbGetRotationalPeriod();
    std::cout << "Rotational period is " << period/1000 << " ms (" << 60e6/period << " rpm)" << std::endl;

    return 0;
}
