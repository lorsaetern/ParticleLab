#include "Particle2.h"
using namespace sf;

bool Particle2::almostEqual(double a, double b, double eps)
{
    return fabs(a - b) < eps;
}

void Particle2::unitTests()
{
    int score = 0;

    cout << "Testing RotationMatrix constructor...";
    double theta = _M_PI / 4.0;
    RotationMatrix r(_M_PI / 4);
    if (r.getRows() == 2 && r.getCols() == 2 && almostEqual(r(0, 0), cos(theta))
        && almostEqual(r(0, 1), -sin(theta))
        && almostEqual(r(1, 0), sin(theta))
        && almostEqual(r(1, 1), cos(theta)))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing ScalingMatrix constructor...";
    ScalingMatrix s(1.5);
    if (s.getRows() == 2 && s.getCols() == 2
        && almostEqual(s(0, 0), 1.5)
        && almostEqual(s(0, 1), 0)
        && almostEqual(s(1, 0), 0)
        && almostEqual(s(1, 1), 1.5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing TranslationMatrix constructor...";
    TranslationMatrix t(5, -5, 3);
    if (t.getRows() == 2 && t.getCols() == 3
        && almostEqual(t(0, 0), 5)
        && almostEqual(t(1, 0), -5)
        && almostEqual(t(0, 1), 5)
        && almostEqual(t(1, 1), -5)
        && almostEqual(t(0, 2), 5)
        && almostEqual(t(1, 2), -5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }


    cout << "Testing Particles..." << endl;
    cout << "Testing Particle mapping to Cartesian origin..." << endl;
    if (m_centerCoordinate.x != 0 || m_centerCoordinate.y != 0)
    {
        cout << "Failed.  Expected (0,0).  Received: (" << m_centerCoordinate.x << "," << m_centerCoordinate.y << ")" << endl;
    }
    else
    {
        cout << "Passed.  +1" << endl;
        score++;
    }

    cout << "Applying one rotation of 90 degrees about the origin..." << endl;
    Matrix initialCoords = m_A;
    rotate(_M_PI / 2.0);
    bool rotationPassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), -initialCoords(1, j)) || !almostEqual(m_A(1, j), initialCoords(0, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            rotationPassed = false;
        }
    }
    if (rotationPassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a scale of 0.5..." << endl;
    initialCoords = m_A;
    scale(0.5);
    bool scalePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 0.5 * initialCoords(0, j)) || !almostEqual(m_A(1, j), 0.5 * initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            scalePassed = false;
        }
    }
    if (scalePassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a translation of (10, 5)..." << endl;
    initialCoords = m_A;
    translate(10, 5);
    bool translatePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 10 + initialCoords(0, j)) || !almostEqual(m_A(1, j), 5 + initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            translatePassed = false;
        }
    }
    if (translatePassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Score: " << score << " / 7" << endl;
}

Particle2::Particle2(RenderTarget& target, int numPoints, Vector2i mouseClickPosition) : m_A(2, numPoints)
{
    m_ttl = TTL2;
    m_numPoints = numPoints;
    m_radiansPerSec = ((float)rand() / (RAND_MAX)*_M_PI);
    m_cartesianPlane.setCenter(0, 0);
    m_cartesianPlane.setSize(target.getSize().x, (-1.0) * target.getSize().y);
    Vector2i point = (mouseClickPosition);
    m_centerCoordinate = target.mapPixelToCoords(point, m_cartesianPlane);
    int numX = ((rand() % (500 - 100 + 1)) + 100);
    int numY = ((rand() % (500 - 100 + 1)) + 100);
    m_vx = numX;
    if (numX % 2 != 0)
    {
        numX *= -1;
        m_vx = numX;
    }
    m_vy = numY;
    Uint8 r = ((rand() % (255 - 0 + 1)) + 0);
    Uint8 g = ((rand() % (255 - 0 + 1)) + 0);
    Uint8 b = ((rand() % (255 - 0 + 1)) + 0);
    m_color1 = Color::White;
    m_color2 = Color::Color(r, g, b);

    float theta = ((float)rand() / (RAND_MAX)*_M_PI / 2);
    float dTheta = 2 * _M_PI / (numPoints - 1);
    for (int j = 0; j < numPoints; j++)
    {
        r = ((rand() % (80 - 20 + 1)) + 20);
        float dx = r * cos(theta);
        float dy = r * sin(theta);
        m_A(0, j) = m_centerCoordinate.x + dx;
        m_A(1, j) = m_centerCoordinate.y + dy;
        theta += dTheta;
    }
}

void Particle2::update(float dt)
{
    float _GG = rand() % 2501 + (-1000);
    m_ttl = m_ttl - dt;
    rotate(dt * m_radiansPerSec);
    scale(SCALE2);
    float dx = m_vx * dt;
    //m_vy = m_vy - (G * dt);
    m_vy = m_vy - (_GG * dt);
    float dy = m_vy * dt;
    translate(dx, dy);
}
void Particle2::draw(RenderTarget& target, RenderStates states) const
{
    VertexArray lines(TriangleStrip, m_numPoints + 1);
    Vector2f center = Vector2f(target.mapCoordsToPixel(m_centerCoordinate, m_cartesianPlane));
    lines[0].position = center;
    lines[0].color = m_color1;
    for (int j = 1; j <= m_numPoints; j++)
    {
        lines[j].position = Vector2f(target.mapCoordsToPixel({ (float)m_A(0, j - 1), (float)m_A(1, j - 1) }, m_cartesianPlane));
        lines[j].color = m_color2;
    }
    target.draw(lines);
}
void Particle2::rotate(double theta)
{
    Vector2f temp = m_centerCoordinate;
    translate(-m_centerCoordinate.x, -m_centerCoordinate.y);
    RotationMatrix R = theta;
    m_A = R * m_A;
    translate(temp.x, temp.y);
}
void Particle2::scale(double c)
{
    Vector2f temp = m_centerCoordinate;
    translate(-m_centerCoordinate.x, -m_centerCoordinate.y);
    ScalingMatrix S = c;
    m_A = S * m_A;
    translate(temp.x, temp.y);
}
void Particle2::translate(double xShift, double yShift)
{
    TranslationMatrix T(xShift, yShift, m_numPoints);
    m_A = T + m_A;
    m_centerCoordinate.x += xShift;
    m_centerCoordinate.y += yShift;
}