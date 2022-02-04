--Dependencies
includedir = {}
includedir["Entt"] =		"%{wks.location}/Nebula/Modules/entt/include"
includedir["ImGui"] =		"%{wks.location}/Nebula/Modules/imgui/include"
includedir["Spdlog"] =		"%{wks.location}/Nebula/Modules/spdlog/include"
includedir["Yaml"] =		"%{wks.location}/Nebula/Modules/yaml-cpp/include"

workspace "Flappy"
	architecture "x86_64"
	startproject "Nebula Storm"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Flappy App
include "Flappy-Bird"