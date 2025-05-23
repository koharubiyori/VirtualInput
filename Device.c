#include "driver.h"
#include "hid.h"
#include "device.tmh"
#include "queueDefault.h"
#include "queueManual.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, CreateDevice)
#endif

HID_REPORT_DESCRIPTOR g_reportDescriptor[] = {
	// Mouse
	0x05, 0x01,        // USAGE_PAGE (Generic Desktop)
	0x09, 0x02,        // USAGE (Mouse)
	0xA1, 0x01,        // COLLECTION (Application)
	0x85,                  REPORT_ID_MOUSE_INPUT,
	0x09, 0x01,            // USAGE_PAGE (Pointer)
	0xA1, 0x00,            // COLLECTION (Physical)
	0x05, 0x09,                // USAGE_PAGE (Buttons)
	0x19, 0x01,                // USAGE_MINIMUM (1)
	0x29, 0x03,                // USAGE_MAXIMUM (3)
	0x15, 0x00,                // LOGICAL_MINIMUM (0)
	0x25, 0x01,                // LOGICAL_MAXIMUM (1)
	0x95, 0x03,                // REPORT_COUNT (3)
	0x75, 0x01,                // REPORT_SIZE (1)
	0x81, 0x02,                // INPUT (Data, Variable, Absolute)
	0x95, 0x01,                // REPORT_COUNT (1)
	0x75, 0x05,                // REPORT_SIZE (5)
	0x81, 0x01,                // INPUT (Constant)
	0x05, 0x01,                // USAGE_PAGE (Generic Desktop)
	0x09, 0x30,                // USAGE (X)
	0x09, 0x31,                // USAGE (Y)
	0x15, 0x81,                // LOGICAL_MINIMUM (-127)
	0x25, 0x7F,                // LOGICAL_MAXIMUM (127)
	0x75, 0x08,                // REPORT_SIZE (8)
	0x95, 0x02,                // REPORT_COUNT (2)
	0x81, 0x06,                // Input (Data, Variable, Relative)
	0xC0,                  // END_COLLECTION
	0xC0,              // END_COLLECTION

	0x05, 0x01,        // USAGE_PAGE (Generic Desktop)
	0x09, 0x00,        // USAGE (Undefined)
	0xa1, 0x01,        // COLLECTION (Application)
	0x85,                  REPORT_ID_MOUSE_OUTPUT,
	0x09, 0x00,            // USAGE (Undefined)
	0x15, 0x00,            // LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,      // LOGICAL_MAXIMUM (255)
	0x95, 0x03,            // REPORT_COUNT (3)
	0x75, 0x08,            // REPORT_SIZE (8)
	0x91, 0x02,            // OUTPUT (Data, Variable, Absolute)
	0xc0,              // END_COLLECTION

	// Keyboard
	0x05, 0x01,        // USAGE_PAGE (Generic Desktop)
	0x09, 0x06,        // USAGE (Keyboard)
	0xA1, 0x01,        // COLLECTION (Application)
	0x85,                  REPORT_ID_KEYBOARD_INPUT,
	0x05, 0x07,            // USAGE_PAGE (Keyboard Key Codes)
	0x19, 0xE0,            // USAGE_MINIMUM (224)
	0x29, 0xE7,            // USAGE_MAXIMUM (231)
	0x15, 0x00,            // LOGICAL_MINIMUM (0)
	0x25, 0x01,            // LOGICAL_MAXIMUM (1)
	0x75, 0x01,            // REPORT_SIZE (1)
	0x95, 0x08,            // REPORT_COUNT (8)
	0x81, 0x02,            // INPUT (Data, Variable, Absolute)
	0x95, 0x01,            // REPORT_COUNT (1)
	0x75, 0x08,            // REPORT_SIZE (8)
	0x81, 0x01,            // INPUT (Constant)
	0x19, 0x00,            // USAGE_MINIMUM (0)
	0x29, 0x65,            // USAGE_MAXIMUM (101)
	0x15, 0x00,            // LOGICAL_MINIMUM (0)
	0x25, 0x65,            // LOGICAL_MAXIMUM (101)
	0x95, 0x06,            // REPORT_COUNT (6)
	0x75, 0x08,            // REPORT_SIZE (8)
	0x81, 0x00,            // INPUT (Data, Array, Absolute)
	0x05, 0x08,            // USAGE_PAGE (LEDs)
	0x19, 0x01,            // USAGE_MINIMUM (Num Lock)
	0x29, 0x05,            // USAGE_MAXIMUM (Kana)
	0x95, 0x05,            // REPORT_COUNT (5)
	0x75, 0x01,            // REPORT_SIZE (1)
	0x91, 0x02,            // OUTPUT (Data, Variable, Absolute)
	0x95, 0x01,            // REPORT_COUNT (1)
	0x75, 0x03,            // REPORT_SIZE (3)
	0x91, 0x01,            // OUTPUT (Constant)
	0xC0,              // END_COLLECTION

	0x05, 0x01,        // USAGE_PAGE (Generic Desktop)
	0x09, 0x00,        // USAGE (Undefined)
	0xa1, 0x01,        // COLLECTION (Application)
	0x85,                  REPORT_ID_KEYBOARD_OUTPUT,
	0x09, 0x00,            // USAGE (Undefined)
	0x15, 0x00,            // LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,      // LOGICAL_MAXIMUM (255)
	0x95, 0x08,            // REPORT_COUNT (8)
	0x75, 0x08,            // REPORT_SIZE (8)
	0x91, 0x02,            // OUTPUT (Data, Variable, Absolute)
	0xc0,              // END_COLLECTION

	// Absolute Mouse
	0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
	0x09, 0x02,                    // USAGE (Mouse)
	0xA1, 0x01,                    // COLLECTION (Application)
	0x85, REPORT_ID_MOUSE_ABS_INPUT,

	0x09, 0x01,                  //   USAGE (Pointer)
	0xA1, 0x00,                  //   COLLECTION (Physical)

	0x05, 0x09,                //     USAGE_PAGE (Buttons)
	0x19, 0x01,                //     USAGE_MINIMUM (Button 1)
	0x29, 0x03,                //     USAGE_MAXIMUM (Button 3)
	0x15, 0x00,                //     LOGICAL_MINIMUM (0)
	0x25, 0x01,                //     LOGICAL_MAXIMUM (1)
	0x95, 0x03,                //     REPORT_COUNT (3)
	0x75, 0x01,                //     REPORT_SIZE (1)
	0x81, 0x02,                //     INPUT (Data, Variable, Absolute)

	0x95, 0x01,                //     REPORT_COUNT (1)
	0x75, 0x05,                //     REPORT_SIZE (5)
	0x81, 0x01,                //     INPUT (Constant) ; padding

	0x05, 0x01,                //     USAGE_PAGE (Generic Desktop)
	0x09, 0x30,                //     USAGE (X)
	0x09, 0x31,                //     USAGE (Y)
	0x16, 0x00, 0x00,          //     LOGICAL_MINIMUM (0)
	0x26, 0xFF, 0x7F,          //     LOGICAL_MAXIMUM (32767)
	0x75, 0x10,                //     REPORT_SIZE (16)
	0x95, 0x02,                //     REPORT_COUNT (2)
	0x81, 0x02,                //     INPUT (Data, Variable, Absolute)

	0xC0,                        //   END_COLLECTION
	0xC0,

	0x05, 0x01,              // USAGE_PAGE (Generic Desktop)
	0x09, 0x00,              // USAGE (Undefined)
	0xA1, 0x01,              // COLLECTION (Application)
	0x85, REPORT_ID_MOUSE_ABS_OUTPUT,
	0x09, 0x00,            //   USAGE (Undefined) - 占位
	0x15, 0x00,            //   LOGICAL_MINIMUM (0)
	0x25, 0xFF,            //   LOGICAL_MAXIMUM (255)
	0x75, 0x08,            //   REPORT_SIZE (8 bits)
	0x95, 0x01,            //   REPORT_COUNT (1 byte for key)
	0x91, 0x02,            //   OUTPUT (Data, Variable, Absolute)

	0x09, 0x30,            //   USAGE (X)
	0x09, 0x31,            //   USAGE (Y)
	0x15, 0x00,            //   LOGICAL_MINIMUM (0)
	0x26, 0xFF, 0x7F,      //   LOGICAL_MAXIMUM (32767)
	0x75, 0x10,            //   REPORT_SIZE (16 bits)
	0x95, 0x02,            //   REPORT_COUNT (2 values: x, y)
	0x91, 0x02,            //   OUTPUT (Data, Variable, Absolute)
	0xC0                    // END_COLLECTION
};

HID_DESCRIPTOR g_hidDescriptor = {
		0x09,        // length of HID descriptor
		0x21,        // descriptor type == HID 0x21
		0x0100,      // hid spec release
		0x00,        // country code == Not Specified
		0x01,        // number of HID class descriptors
		{            // DescriptorList[0]
				0x22,                             // report descriptor type 0x22
				sizeof(g_reportDescriptor)        // total length of report descriptor
		}
};

// {3E0CFF6E-F1B8-470E-9D71-C38D3DBC0C29}
static const GUID GUID_MOUSE_DEVICE_INTERFACE =
{ 0x3e0cff6e, 0xf1b8, 0x470e, { 0x9d, 0x71, 0xc3, 0x8d, 0x3d, 0xbc, 0x0c, 0x29 } };

NTSTATUS
CreateDevice(
	_Inout_ PWDFDEVICE_INIT DeviceInit
) {
	NTSTATUS                status = STATUS_SUCCESS;
	WDFDEVICE               device = NULL;
	PDEVICE_CONTEXT         deviceContext = NULL;
	WDF_OBJECT_ATTRIBUTES   deviceAttributes;

	WdfFdoInitSetFilter(DeviceInit);
	TRACE_LEVEL_INFORMATION;

	WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&deviceAttributes, DEVICE_CONTEXT);

	status = WdfDeviceCreate(&DeviceInit, &deviceAttributes, &device);
	if (!NT_SUCCESS(status)) {
		TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "WdfDeviceCreate Entry");
		return status;
	}

	deviceContext = DeviceGetContext(device);
	deviceContext->device = device;
	deviceContext->queueDefault = NULL;
	deviceContext->queueManual = NULL;
	deviceContext->hidDescriptor = &g_hidDescriptor;
	deviceContext->hidReportDescriptor = g_reportDescriptor;

	RtlZeroMemory(&deviceContext->hidDeviceAttributes, sizeof(HID_DEVICE_ATTRIBUTES));
	deviceContext->hidDeviceAttributes.Size = sizeof(HID_DEVICE_ATTRIBUTES);
	deviceContext->hidDeviceAttributes.VendorID = VENDOR_ID;
	deviceContext->hidDeviceAttributes.ProductID = PRODUCT_ID;
	deviceContext->hidDeviceAttributes.VersionNumber = VERSION_NUMBER;

	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "WdfDeviceCreateDeviceInterface Entry");

	status = WdfDeviceCreateDeviceInterface(device, &GUID_MOUSE_DEVICE_INTERFACE, NULL);

	if (!NT_SUCCESS(status)) {
		TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "WdfDeviceCreateDeviceInterface failed %!STATUS!", status);
		return status;
	}

	status = QueueDefaultCreate(device, &deviceContext->queueDefault);
	if (!NT_SUCCESS(status)) {
		TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "QueueDefaultCreate failed %!STATUS!", status);
		return status;
	}

	status = QueueManualCreate(device, &deviceContext->queueManual);

	if (!NT_SUCCESS(status)) {
		TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "QueueManualCreate failed %!STATUS!", status);
	}

	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "WdfDeviceCreateDeviceInterface Exit");

	return status;
}
