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

#include "plugin-entry.hh" // <clap/helpers/plugin-entry.hh>

struct clap_plugin_info_as_auv2;
struct clap_plugin_factory_as_auv2;

namespace sapphire_plugins
{
using Entry =
    clap::helpers::PluginEntry<clap::helpers::MisbehaviourHandler::Terminate,
                               clap::helpers::CheckingLevel::Maximal>; // those hard requirements
                                                                       // have to be checked with
                                                                       // different hosts
struct EntryImpl : Entry
{
    const void *getFactory(const char *factory_id) const noexcept override;
    bool init(const char *p) noexcept override;
    bool implementsPluginFactory() const noexcept override { return true; }
    uint32_t pluginFactoryGetPluginCount() const noexcept override;
    const clap_plugin_descriptor *
    pluginFactoryGetPluginDescriptor(uint32_t w) const noexcept override;
    const clap_plugin *pluginFactoryCreatePlugin(const clap_host &host,
                                                 const char *plugin_id) const noexcept override;

protected:
    bool getAuv2Info(uint32_t index, clap_plugin_info_as_auv2 *info) const noexcept;

private:
    static bool clapGetAuv2Info(const clap_plugin_factory_as_auv2 *factory, uint32_t index,
                                clap_plugin_info_as_auv2 *info) noexcept;
};
} // namespace sapphire_plugins
