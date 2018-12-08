#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Math {
public:

    static glm::mat4 createTransformationMatrix(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale)
    {
        glm::mat4 transform(1.0f);
        transform = glm::translate(transform, position);
        transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1,0,0));
        transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0,1,0));
        transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0,0,1));
        transform = glm::scale(transform, scale);
        return transform;
    }

    static glm::mat4 createTransformationMatrix(const glm::vec2 position, const glm::vec2 rotation, const glm::vec2 scale)
    {
        glm::mat4 transform(1.0f);
        transform = glm::translate(transform, glm::vec3(position.x, position.y, 0.0f));
        transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1,0,0));
        transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0,1,0));
        transform = glm::rotate(transform, glm::radians(0.0f), glm::vec3(0,0,1));
        transform = glm::scale(transform, glm::vec3(scale.x, scale.y, 1.0f));
        return transform;
    }
};