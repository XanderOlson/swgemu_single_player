#include "gtest/gtest.h"

#include "server/zone/objects/tangible/attachment/Attachment.h"
#include "system/lang/UnicodeString.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace attachment {
namespace test {

TEST(AttachmentNameTest, RefreshCustomNameAddsSkillMods) {
	Reference<Attachment*> attachment = new Attachment();

	attachment->setCustomObjectName(UnicodeString("Armor Attachment"), false);

	auto skillMods = attachment->getSkillMods();
	ASSERT_NE(skillMods, nullptr);

	skillMods->put("aim", 5);

	attachment->refreshCustomName(false);

	String name = attachment->getCustomObjectName().toString();

	EXPECT_NE(name.indexOf("Armor Attachment"), -1);
	EXPECT_NE(name.indexOf("aim"), -1);
	EXPECT_NE(name.indexOf("+5"), -1);
}

} // namespace test
} // namespace attachment
} // namespace tangible
} // namespace objects
} // namespace zone
} // namespace server
