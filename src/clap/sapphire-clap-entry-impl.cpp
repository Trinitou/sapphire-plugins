/*
 * Sapphire Plugins
 *
 * Bringing the magical world of CosineKitty's sapphire plugins for rack to your DAW
 *
 * Copyright 2024-2025, Don Cross, Paul Walker, Morgon Kanter and other authors, as
 * described in the github transaction log.
 *
 * This project is distributed under the Gnu General Public License, version 3.0 or later.
 * You can find the LICENSE file at the address below.
 *
 * The source code and license are at https://github.com/baconpaul/sapphire-plugins
 */

#include "configuration.h"
#include "sst/plugininfra/version_information.h"
#include "clap/sapphire-clap-entry-impl.h"
#include "clap/plugin.h"
#include "clapwrapper/vst3.h"
#include "clapwrapper/auv2.h"

#include <iostream>
#include <cstring>
#include <string.h>
#include <clap/clap.h>
#include "plugin-entry.hxx" // <clap/helpers/plugin-entry.hxx>

#include "elastika/elastika.h"
#include "tube_unit/tube_unit.h"
#include "gravy/gravy.h"
#include "galaxy/galaxy.h"

template const clap_plugin_entry sapphire_plugins::Entry::clapPluginEntry<sapphire_plugins::EntryImpl>() noexcept;

namespace sapphire_plugins
{

uint32_t sapphire_plugins::EntryImpl::pluginFactoryGetPluginCount() const noexcept { return 4; };
const clap_plugin_descriptor *sapphire_plugins::EntryImpl::pluginFactoryGetPluginDescriptor(uint32_t w) const noexcept
{
    if (w == 0)
    {
        return elastika::getDescriptor();
    }

    if (w == 1)
    {
        return tube_unit::getDescriptor();
    }

    if (w == 2)
    {
        return gravy::getDescriptor();
    }

    if (w == 3)
    {
        return galaxy::getDescriptor();
    }

    return nullptr;
}

const clap_plugin *
sapphire_plugins::EntryImpl::pluginFactoryCreatePlugin(const clap_host &host,
                                      const char *plugin_id) const noexcept
{
    if (strcmp(plugin_id, elastika::getDescriptor()->id) == 0)
    {
        return elastika::makePlugin(&host);
    }
    if (strcmp(plugin_id, tube_unit::getDescriptor()->id) == 0)
    {
        return tube_unit::makePlugin(&host);
    }

    if (strcmp(plugin_id, gravy::getDescriptor()->id) == 0)
    {
        return gravy::makePlugin(&host);
    }

    if (strcmp(plugin_id, galaxy::getDescriptor()->id) == 0)
    {
        return galaxy::makePlugin(&host);
    }
    return nullptr;
}

static bool clap_get_auv2_info(const clap_plugin_factory_as_auv2 *factory, uint32_t index,
                               clap_plugin_info_as_auv2_t *info)
{
    if (index == 0)
    {
        strncpy(info->au_type, "aufx", 5); // use the features to determine the type
        strncpy(info->au_subt, "elas", 5);

        return true;
    }

    if (index == 1)
    {
        strncpy(info->au_type, "aufx", 5); // use the features to determine the type
        strncpy(info->au_subt, "tbun", 5);

        return true;
    }

    if (index == 2)
    {
        strncpy(info->au_type, "aufx", 5); // use the features to determine the type
        strncpy(info->au_subt, "grvy", 5);

        return true;
    }

    if (index == 3)
    {
        strncpy(info->au_type, "aufx", 5); // use the features to determine the type
        strncpy(info->au_subt, "glxy", 5);

        return true;
    }

    return false;
}

static const clap_plugin_info_as_vst3 *clap_get_vst3_info(const clap_plugin_factory_as_vst3 *f,
                                                          uint32_t index)
{
    return nullptr;
}

const void *sapphire_plugins::EntryImpl::getFactory(const char *factory_id) const noexcept
{
    SPLLOG("Asking for factory [" << factory_id << "]");
    if (strcmp(factory_id, CLAP_PLUGIN_FACTORY_INFO_AUV2) == 0)
    {
        static const struct clap_plugin_factory_as_auv2 six_sines_auv2_factory = {
            "SPhR",    // manu
            "Saphire", // manu name
            clap_get_auv2_info};
        return &six_sines_auv2_factory;
    }
    if (strcmp(factory_id, CLAP_PLUGIN_FACTORY_INFO_VST3) == 0)
    {
        static const struct clap_plugin_factory_as_vst3 six_sines_vst3_factory = {
            "Sapphire", "", "", clap_get_vst3_info};

        return &six_sines_vst3_factory;
    }
    return nullptr;
}

bool sapphire_plugins::EntryImpl::init(const char *p) noexcept {
    // sst::plugininfra::misc_platform::allocateConsole();
    SPLLOG("Initializing Sapphire");
    return true;
}
} // namespace sapphire_plugins