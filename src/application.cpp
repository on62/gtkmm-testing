/* -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
#include <config.h>

#include <glib/gi18n.h>
#include <gtkmm/builder.h>
#include <signal.h>
#include "application.hpp"

#include <iostream>

void GsmApplication::load_settings() {
}

GsmApplication::GsmApplication()
    : Gtk::Application("com.mktneutral.gtkmm_testing", Gio::APPLICATION_HANDLES_COMMAND_LINE)
{
    Glib::set_application_name(_("gtkmm_testing"));
}

Glib::RefPtr<GsmApplication> GsmApplication::get () {
    static Glib::RefPtr<GsmApplication> singleton;
    if (!singleton) {
        singleton = Glib::RefPtr<GsmApplication>(new GsmApplication());
    }
    return singleton;
}

void GsmApplication::on_activate() {
    Glib::RefPtr<Gtk::CssProvider> cssProvider = Gtk::CssProvider::create();
    cssProvider->load_from_resource("/org/gnome/gtkmm-testing/data/interface.css");

    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
    builder->add_from_resource("/org/gnome/gtkmm-testing/data/interface.ui");

    Glib::RefPtr<Gtk::Window> rootWindow = Glib::RefPtr<Gtk::Window>::cast_static(builder->get_object("window"));
    Glib::RefPtr<Gdk::Screen> screen = rootWindow->get_screen();
    Gtk::StyleContext::add_provider_for_screen(screen, cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);

    Glib::RefPtr<Gtk::EventBox> tickerColumnHeader = Glib::RefPtr<Gtk::EventBox>::cast_static(builder->get_object("ticker_column_header"));
    tickerColumnHeader->set_events(Gdk::BUTTON_PRESS_MASK);
    tickerColumnHeader->signal_button_press_event().connect( sigc::mem_fun(*this, &GsmApplication::onTickerColumnHeaderClicked) );

    Glib::RefPtr<Gtk::EventBox> shareCountColumnHeader = Glib::RefPtr<Gtk::EventBox>::cast_static(builder->get_object("share_count_column_header"));
    shareCountColumnHeader->set_events(Gdk::BUTTON_PRESS_MASK);
    shareCountColumnHeader->signal_button_press_event().connect( sigc::mem_fun(*this, &GsmApplication::onShareCountColumnHeaderClicked) );

    Glib::RefPtr<Gtk::EventBox> shareBasisColumnHeader = Glib::RefPtr<Gtk::EventBox>::cast_static(builder->get_object("share_basis_column_header"));
    shareBasisColumnHeader->set_events(Gdk::BUTTON_PRESS_MASK);
    shareBasisColumnHeader->signal_button_press_event().connect( sigc::mem_fun(*this, &GsmApplication::onShareBasisColumnHeaderClicked) );

    add_window(*(rootWindow.get()));

    rootWindow->present();
}

int GsmApplication::on_command_line(const Glib::RefPtr<Gio::ApplicationCommandLine>& command_line) {
    int argc = 0;
    char** argv = command_line->get_arguments(argc);

    on_activate();

    return 0;
}

void GsmApplication::shutdown() {
    quit();
}

void GsmApplication::on_startup() {
    Gtk::Application::on_startup();

    load_resources();
}

void GsmApplication::load_resources() {
}

bool GsmApplication::onTickerColumnHeaderClicked(GdkEventButton* button_event) {
    std::cout << "YOU CLICKED THE TICKER COLUMN HEADER." << std::endl;
    return true;
}

bool GsmApplication::onShareCountColumnHeaderClicked(GdkEventButton* button_event) {
    std::cout << "YOU CLICKED THE SHARE COUNT COLUMN HEADER." << std::endl;
    return true;
}

bool GsmApplication::onShareBasisColumnHeaderClicked(GdkEventButton* button_event) {
    std::cout << "YOU CLICKED THE SHARE BASIS COLUMN HEADER." << std::endl;
    return true;
}
