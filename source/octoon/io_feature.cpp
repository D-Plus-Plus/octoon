#if defined(OCTOON_FEATURE_IO_ENABLE)
#include <octoon/io_feature.h>
#include <octoon/io/ioserver.h>
#include <octoon/io/farchive.h>

namespace octoon
{
	OctoonImplementSubClass(IOFeature, GameFeature, "IOFeature")

	IOFeature::IOFeature() noexcept
		: system_path_("../../system")
	{
	}

	IOFeature::~IOFeature() noexcept
	{
	}

	void
	IOFeature::on_activate() except
	{
		io::IoServer::instance()->mount_archive("sys", std::make_shared<octoon::io::farchive>(system_path_));
	}

	void
	IOFeature::on_deactivate() noexcept
	{
		io::IoServer::instance()->unmount_archive("sys");
	}

	void
	IOFeature::on_frame_begin() noexcept
	{
	}

	void
	IOFeature::on_frame() noexcept
	{
	}

	void
	IOFeature::on_frame_end() noexcept
	{
	}
}
#endif