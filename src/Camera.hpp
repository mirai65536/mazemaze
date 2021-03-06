/*
 * Copyright (c) 2019, Мира Странная <rsxrwscjpzdzwpxaujrr@yahoo.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

namespace mazemaze {

class Camera {
public:
    explicit Camera(float  x,     float  y,        float  z,
                    float  pitch, float  yaw,      float  roll,
                    double fov,   double nearDist, double farDist);
    ~Camera();

    void setupRotation();
    void setupTranslation();
    void setupPerspective();

    float getX() const;
    float getY() const;
    float getZ() const;

    float getPitch() const;
    float getYaw() const;
    float getRoll() const;

    double getFov() const;

    void setX(float x);
    void setY(float y);
    void setZ(float z);

    void setPitch(float pitch);
    void setYaw(float yaw);
    void setRoll(float roll);

    void setFov(double fov);

private:
    float x;
    float y;
    float z;

    float pitch;
    float yaw;
    float roll;

    double fov;
    double nearDist;
    double farDist;
};

}
