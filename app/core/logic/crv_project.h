#pragma once

#include "../../utils/types/bytes.h"
#include "../graphics/formats/crv_commonimage.h"
#include "../graphics/formats/crv_bitmap.h"
#include "../graphics/objects/crv_object.h"

#include <memory>
#include <string>
#include <vector>
#include <cstdint>

class CRV_Project {
public:
	/* @brief Creates a new project with default settings.
	 *
	 * @return A unique pointer to the newly created project.
	 */
	static std::unique_ptr<CRV_Project> Create();

	/* @brief Loads a project from the specified file path.
	 *
	 * @param filePath The path to the project file.
	 *
	 * @return A unique pointer to the loaded project, or nullptr if loading failed.
	 */
	static std::unique_ptr<CRV_Project> Create(const std::string& filePath);

	/* @brief Loads a project from the specified file path.
	 *
	 * @param filePath The path to the project file.
	 *
	 * @return A unique pointer to the loaded project, or nullptr if loading failed.
	 */
	static std::unique_ptr<CRV_Project> Create(const std::wstring& filePath);

	/* @brief Loads a project from the given byte stream.
	 *
	 * @param stream The byte stream containing the project data.
	 * 
	 * @return A unique pointer to the loaded project, or nullptr if loading failed.
	 */
	static std::unique_ptr<CRV_Project> Create(crv::type::ByteStream& stream);

	/* @brief Saves the project and returns a byte stream containing the project data.
	 *
	 * @return A byte stream containing the saved project data.
	 */
	crv::type::ByteStream DoSaveCopy() const;

	/* @brief Paints the project onto the given common image and returns the painted image.
	 *
	 * @param commonImage The common image to paint on. Must not be nullptr.
	 *
	 * @return A unique pointer to the painted common image, or nullptr if painting failed.
	 * 
	 * @note During painting, the project will own the image, then return it back to the caller with modifications.
	 */
	template<CommonImageType T = crv::graphics::Bitmap>
	std::unique_ptr<T> DoPaint(std::unique_ptr<T> commonImage) const;

	/* @brief Gets the width of the project canvas.
	 *
	 * @return The width of the project canvas in pixels.
	 */
	int GetWidth() const;

	/* @brief Sets the width of the project canvas.
	 *
	 * @param width The new width of the project canvas in pixels.
	 */
	void SetWidth(int width);

	/* @brief Gets the height of the project canvas.
	 *
	 * @return The height of the project canvas in pixels.
	 */
	int GetHeight() const;

	/* @brief Sets the height of the project canvas.
	 *
	 * @param height The new height of the project canvas in pixels.
	 */
	void SetHeight(int height);

	/* @brief Adds a graphic object to the project.
	 *
	 * @param annotation The graphic object to add. Must not be nullptr.
	 */
	void AddGraphicObject(std::unique_ptr<crv::graphics::Object> annotation);

	/* @brief Gets the number of graphic objects in the project.
	 *
	 * @return The number of graphic objects in the project.
	 */
	size_t GetObjectCount() const;

	/* @brief Gets the graphic object at the specified index.
	 *
	 * @param index The index of the graphic object to retrieve. Must be less than GetObjectCount().
	 *
	 * @return A shared pointer to the graphic object at the specified index, or nullptr if the index is out of range.
	 */
	const std::shared_ptr<crv::graphics::Object> GetObject(size_t index) const;

	/* @brief Gets a mutable reference to the graphic object at the specified index.
	 *
	 * @param index The index of the graphic object to retrieve. Must be less than GetObjectCount().
	 *
	 * @return A shared pointer to the graphic object at the specified index, or nullptr if the index is out of range.
	 */
	std::shared_ptr<crv::graphics::Object> GetMutableObject(size_t index);

	/* @brief Removes the graphic object at the specified index.
	 *
	 * @param index The index of the graphic object to remove. Must be less than GetObjectCount().
	 */
	void RemoveObjectAtIndex(size_t index);

	/* @brief Gets the creation date of the project.
	 *
	 * @return The creation date of the project as a string.
	 */
	std::string GetCreationDate() const;

	/* @brief Sets the creation date of the project.
	 *
	 * @param creationDate The new creation date of the project as a string.
	 */
	void SetCreationDate(const std::string& creationDate);

	/* @brief Gets the modification date of the project.
	 *
	 * @return The modification date of the project as a string.
	 */
	std::string GetModificationDate() const;

	/* @brief Sets the modification date of the project.
	 * 
	 * @param modificationDate The new modification date of the project as a string.
	 */
	void SetModificationDate(const std::string& modificationDate);

protected:
	CRV_Project() = default;
private:
	int _width = 2481;
	int _height = 3507;
	std::vector<std::shared_ptr<crv::graphics::Object>> _objects{};
	std::string _creationDate{};
	std::string _modificationDate{};
	uint32_t _nextObjNum = 0;
};

#include "crv_project.inl"