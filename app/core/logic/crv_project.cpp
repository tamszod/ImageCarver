#include "crv_project.h"
#include "crv_projectload.h"
#include "crv_projectsave.h"
#include "../../utils/helpers/time.h"

#include <fstream>
#include <filesystem>

std::unique_ptr<CRV_Project> CRV_Project::Create() {
	return std::unique_ptr<CRV_Project>(new CRV_Project());
}

std::unique_ptr<CRV_Project> CRV_Project::Create(const std::string& filePath) {
	return Create(std::filesystem::path(filePath).wstring());
}

std::unique_ptr<CRV_Project> CRV_Project::Create(const std::wstring& filePath) { // fails
	std::ifstream file(std::filesystem::path(filePath), std::ios::binary);
	if (!file) {
		return nullptr;
	}

	// Get file size
	file.seekg(0, std::ios::end);
	std::streamsize size = file.tellg();

	// Move back to beginning
	file.seekg(0, std::ios::beg);

	if (size <= 0) {
		return nullptr;
	}

	// Read directly
	crv::type::ByteStream buffer(size);
	if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
		return nullptr;
	}

	return Create(buffer);
}

std::unique_ptr<CRV_Project> CRV_Project::Create(crv::type::ByteStream& stream) {
	CRV_ProjectLoad operation{ stream };
	return operation.Load();
}

crv::type::ByteStream CRV_Project::DoSaveCopy() const {
	CRV_ProjectSave operation(*this);
	return operation.Save();
}

int CRV_Project::GetWidth() const {
	return _width;
}

void CRV_Project::SetWidth(int width) {
	_width = width;
}

int CRV_Project::GetHeight() const {
	return _height;
}

void CRV_Project::SetHeight(int height) {
	_height = height;
}

void CRV_Project::AddGraphicObject(std::unique_ptr<crv::graphics::Object> annotation) {
	if (!annotation) {
		return;
	}
	if (!annotation->GetObjNum()) {
		annotation->SetOjbNum(++_nextObjNum);
	}
	_objects.emplace_back(std::move(annotation));
}

size_t CRV_Project::GetObjectCount() const {
	return _objects.size();
}

const std::shared_ptr<crv::graphics::Object> CRV_Project::GetObject(size_t index) const {
	if (index >= _objects.size()) {
		return nullptr;
	}
	return _objects[index];
}

std::shared_ptr<crv::graphics::Object> CRV_Project::GetMutableObject(size_t index) {
	if (index >= _objects.size()) {
		return nullptr;
	}
	return _objects[index];
}

void CRV_Project::RemoveObjectAtIndex(size_t index) {
	if (index >= _objects.size()) {
		return;
	}
	_objects.erase(_objects.begin() + index);
}

std::string CRV_Project::GetCreationDate() const {
	if (_creationDate.empty()) {
		return crv::helper::GetQuickTime();
	}
	return _creationDate;
}

void CRV_Project::SetCreationDate(const std::string& creationDate) {
	_creationDate = creationDate;
}

std::string CRV_Project::GetModificationDate() const {
	if (_modificationDate.empty()) {
		return crv::helper::GetQuickTime();
	}
	return _modificationDate;
}

void CRV_Project::SetModificationDate(const std::string& modificationDate) {
	_modificationDate = modificationDate;
}
