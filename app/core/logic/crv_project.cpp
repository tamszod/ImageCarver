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

std::unique_ptr<CRV_Project> CRV_Project::Create(const std::wstring& filePath) {
std::ifstream file(std::filesystem::path(filePath), std::ios::binary);
	if (!file) {
		return nullptr;
	}

	auto size = std::filesystem::file_size(filePath);
	if (size == 0) {
		return nullptr;
	}

	crv::type::ByteStream buffer(size+1);
	if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
		return nullptr;
	}

	if (file.gcount() != size) {
		return nullptr;
	}

	buffer[size] = '\0'; // Add the terminator character early so buffer is allocated once and complete for parsing.

	return Create(std::move(buffer));
}

std::unique_ptr<CRV_Project> CRV_Project::Create(crv::type::ByteStream&& stream) {
	CRV_ProjectLoad operation{ std::move(stream) };
	return operation.Load();
}

crv::type::ByteStream CRV_Project::DoSaveCopy() const {
	CRV_ProjectSave operation(*this);
	return operation.Save();
}

int CRV_Project::GetWidth() const {
	return width_;
}

void CRV_Project::SetWidth(int width) {
    width_ = width;
}

int CRV_Project::GetHeight() const {
	return height_;
}

void CRV_Project::SetHeight(int height) {
	height_ = height;
}

void CRV_Project::AddGraphicalObject(std::unique_ptr<crv::graphics::Object> object) {
	if (!object) {
		return;
	}

	if (!object->GetObjNum()) {
		object->SetOjbNum(++nextObjNum_);
	}

	objects_.emplace_back(std::move(object));
}

size_t CRV_Project::GetObjectCount() const {
	return objects_.size();
}

std::shared_ptr<const crv::graphics::Object> CRV_Project::GetObject(size_t index) const {
	if (index >= objects_.size()) {
		return nullptr;
	}
	return objects_[index];
}

std::shared_ptr<crv::graphics::Object> CRV_Project::GetMutableObject(size_t index) {
	if (index >= objects_.size()) {
		return nullptr;
	}
	return objects_[index];
}

void CRV_Project::RemoveObjectAtIndex(size_t index) {
	if (index >= objects_.size()) {
		return;
	}
	objects_.erase(objects_.begin() + index);
}

std::string CRV_Project::GetCreationDate() const {
	if (creationDate_.empty()) {
		return crv::helper::GetQuickTime();
	}
	return creationDate_;
}

void CRV_Project::SetCreationDate(const std::string& creationDate) {
	creationDate_ = creationDate;
}

std::string CRV_Project::GetModificationDate() const {
	if (modificationDate_.empty()) {
		return crv::helper::GetQuickTime();
	}
	return modificationDate_;
}

void CRV_Project::SetModificationDate(const std::string& modificationDate) {
	modificationDate_ = modificationDate;
}