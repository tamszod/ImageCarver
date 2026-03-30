#include "../utilities/types/crv_color.h"
#include "../core/graphics/formats/crv_bitmap.h"
#include "../core/graphics/objects/crv_lineobject.h"
#include "../core/graphics/objects/crv_rectangleobject.h"
#include "../core/graphics/objects/crv_ovalobject.h"

#include "../core/logic/crv_project.h"

#include <iostream>
#include <fstream>

int main() {
	// Create graphic objects
	auto line = std::make_unique<crv::graphics::LineObject>();
	line->SetColor(CRV_Color::Create(255, 0, 0));
	line->SetLineWidth(5);
	line->SetStartPoint({ 95.85f, 98.55f });
	line->SetEndPoint({ 100.65f,  325.45f });

	auto rectangle = std::make_unique<crv::graphics::RectangleObject>();
	rectangle->SetColor(CRV_Color::Create(200, 200, 100));
	rectangle->SetFillColor(CRV_Color::Create(0, 0, 0));
	rectangle->SetLineWidth(2);
	rectangle->SetBBox({ 493.54f, 900.43f, 1498.43f, 2000.99f });

	auto oval = std::make_unique<crv::graphics::OvalObject>();
	oval->SetColor(CRV_Color::Create(151, 151, 252));
	oval->SetFillColor(CRV_Color::Create(45, 99, 99));
	oval->SetLineWidth(10);
	oval->SetBBox({ 493.54f, 900.43f, 1498.43f, 2000.99f });

	// Create project and add objects
	auto project = CRV_Project::Create();
	project->AddGraphicObject(std::move(line));
	project->AddGraphicObject(std::move(rectangle));
	project->AddGraphicObject(std::move(oval));

	// Paint project to bitmap and save as BMP file
	std::unique_ptr<CRV_Bitmap> bitmap = CRV_Bitmap::Create(project->GetWidth(), project->GetHeight(), CRV_Bitmap::ColorMode::RGB);
	bitmap = project->DoPaint(std::move(bitmap));
	auto bitmapData = bitmap->Export(CRV_ImageFormat::BMP);
	std::ofstream bitmapFile("test.bmp", std::ios::binary);
	bitmapFile.write(reinterpret_cast<const char*>(bitmapData.data()), bitmapData.size());
	bitmapFile.close();

	// Save project to file
	auto data = project->DoSaveCopy();
	std::ofstream projectFile("test.crv", std::ios::binary);
	projectFile.write(reinterpret_cast<const char*>(data.data()), data.size());
	projectFile.close();

	// Load project from file and paint again to verify correctness
	auto reloadedProject = CRV_Project::Create("test.crv");
	std::unique_ptr<CRV_Bitmap> reloadedBitmap = CRV_Bitmap::Create(reloadedProject->GetWidth(), reloadedProject->GetHeight(), CRV_Bitmap::ColorMode::RGB);
	reloadedBitmap = reloadedProject->DoPaint(std::move(reloadedBitmap));
	auto reloadedBitmapData = bitmap->Export(CRV_ImageFormat::BMP);
	std::ofstream reloadedBitmapFile("reloded.bmp", std::ios::binary);
	reloadedBitmapFile.write(reinterpret_cast<const char*>(reloadedBitmapData.data()), reloadedBitmapData.size());
	reloadedBitmapFile.close();
	return 0;
}