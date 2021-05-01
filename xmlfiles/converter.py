import math

planetas = {
    "sol": {
        "translate": None,
        "angle": 7,
        "rotate": 600,
        "scale": 80,
        "colour": [255, 140, 0],
        "model": "sphere.3d",
        "moons": None
    },
    "mercurio": {
        "translate": [88, 100],
        "angle": None,
        "rotate": 1408,
        "scale": 2,
        "colour": [186, 184, 181],
        "model": "sphere.3d",
        "moons": None
    },
    "venus": {
        "translate": [225, 200],
        "angle": -3,
        "rotate": 5832,
        "scale": 3,
        "colour": [237, 184, 100],
        "model": "sphere.3d",
        "moons": None
    },
    "terra": {
        "translate": [365, 300],
        "angle": 23.5,
        "rotate": 24,
        "scale": 3.57,
        "colour": [61, 129, 224],
        "model": "sphere.3d",
        "moons": {
            "lua": {
                "translate": [27, 30],
                "angle": 6.68,
                "rotate": 29.5,
                "scale": 1,
                "colour": [207, 207, 207],
                "model": "sphere.3d",
                "moons": None
            }
        }
    },
    "marte": {
        "translate": [687, 400],
        "angle": 25,
        "rotate": 25,
        "scale": 2,
        "colour": [240, 95, 70],
        "model": "sphere.3d",
        "moons": None
    },
    "jupiter": {
        "translate": [4380, 600],
        "angle": 3,
        "rotate": 10,
        "scale": 40,
        "colour": [169, 148, 179],
        "model": "sphere.3d",
        "moons": {
            "io": {
                "translate": [1.75, 40],
                "angle": None,
                "rotate": 42.48,
                "scale": 0.5,
                "colour": [209, 150, 23],
                "model": "sphere.3d",
                "moons": None
            },
            "europa": {
                "translate": [3.54, 45],
                "angle": None,
                "rotate": 84,
                "scale": 0.5,
                "colour": [141, 152, 131],
                "model": "sphere.3d",
                "moons": None
            },
            "ganymede": {
                "translate": [7.16, 50],
                "angle": None,
                "rotate": 168,
                "scale": 0.5,
                "colour": [95, 99, 150],
                "model": "sphere.3d",
                "moons": None
            },
            "calisto": {
                "translate": [17, 55],
                "angle": None,
                "rotate": 384,
                "scale": 0.5,
                "colour": [150, 101, 24],
                "model": "sphere.3d",
                "moons": None
            }
        }
    },
    "saturno": {
        "translate": [10585, 700],
        "angle": 27,
        "rotate": 11,
        "scale": 34,
        "colour": [196, 196, 104],
        "model": "sphere.3d",
        "moons": {
            "inner_rings" : {
                "translate": None,
                "angle": None,
                "rotate": None,
                "scale": 12.75,
                "colour": [255, 204, 102],
                "model": "ring.3d",
                "moons": None
            },
            "outer_rings": {
                "translate": None,
                "angle": None,
                "rotate": None,
                "scale": 16.15,
                "colour": [176, 142, 84],
                "model": "ring.3d",
                "moons": None
            }
        }
    },
    "urano": {
        "translate": [30660, 800],
        "angle": -82,
        "rotate": 17,
        "scale": 7.1,
        "colour": [61, 194, 201],
        "model": "sphere.3d",
        "moons": {
            "rings": {
                "translate": None,
                "angle": None,
                "rotate": None,
                "scale": 8,
                "colour": [100, 100, 100],
                "model": "uranusRing.3d",
                "moons": None
            }
        }
    },
    "neptuno": {
        "translate": [60225, 900],
        "angle": 30,
        "rotate": 16,
        "scale": 6.8,
        "colour": [6, 78, 194],
        "model": "sphere.3d",
        "moons": None
    },
    "plutao": {
        "translate": [90520, 1000],
        "angle": -72,
        "rotate": 153,
        "scale": 3,
        "colour": [186, 143, 227],
        "model": "sphere.3d",
        "moons": None
    }
}

def printPlaneta(name, p, pscale):
    print("<!-- " + name.capitalize() + "-->")
    print("<group>")

    if p["translate"]:
        y = p["translate"][0] * 30 / 365

        size = p["translate"][1]/pscale
        size /= 2

        x1 = 0
        x2 = ((2-math.sqrt(2))*math.sqrt(4+2*math.sqrt(2))) * size / 4
        x3 = math.sqrt(2)/2*size
        x4 = ((2+math.sqrt(2))*math.sqrt(4-2*math.sqrt(2))) * size/4
        x5 = size
        print("<translate time=\"" + str(y) + "\">")
        print("<point X=\"" + str(x5) + "\" Z=\"" + str(x1) + "\"/>")
        print("<point X=\"" + str(x4) + "\" Z=\"" + str((-x2)) + "\"/>")
        print("<point X=\"" + str(x3) + "\" Z=\"" + str((-x3)) + "\"/>")
        print("<point X=\"" + str(x2) + "\" Z=\"" + str((-x4)) + "\"/>")
        print("<point X=\"" + str(x1) + "\" Z=\"" + str((-x5)) + "\"/>")
        print("<point X=\"" + str((-x2)) + "\" Z=\"" + str((-x4)) + "\"/>")
        print("<point X=\"" + str((-x3)) + "\" Z=\"" + str((-x3)) + "\"/>")
        print("<point X=\"" + str((-x4)) + "\" Z=\"" + str((-x2)) + "\"/>")
        print("<point X=\"" + str((-x5)) + "\" Z=\"" + str(x1) + "\"/>")
        print("<point X=\"" + str((-x4)) + "\" Z=\"" + str(x2) + "\"/>")
        print("<point X=\"" + str((-x3)) + "\" Z=\"" + str(x3) + "\"/>")
        print("<point X=\"" + str((-x2)) + "\" Z=\"" + str(x4) + "\"/>")
        print("<point X=\"" + str(x1) + "\" Z=\"" + str(x5) + "\"/>")
        print("<point X=\"" + str(x2) + "\" Z=\"" + str(x4) + "\"/>")
        print("<point X=\"" + str(x3) + "\" Z=\"" + str(x3) + "\"/>")
        print("<point X=\"" + str(x4) + "\" Z=\"" + str(x2) + "\"/>")
        print("</translate>")
    
    if p["angle"]:
        print("<rotate angle=\"" + str(p["angle"]) + "\" axisX=\"1\" />")

    if p["rotate"]:
        y = p["rotate"] * 10 / 24
        print("<rotate time=\"" + str(y) + "\" axisY=\"1\" />")


    if name in ["sol", "jupiter", "saturno"]:
        scale = p["scale"]/2/pscale
    else:
        scale = p["scale"]*1.5/pscale

    scale /= 2
    print("<scale X=\"" + str(scale) + "\" Y=\"" + str(scale) + "\" Z=\"" + str(scale) + "\" />")
    
    if p["colour"]:
        print("<colour R=\"" + str(p["colour"][0]) +
              "\" G=\"" + str(p["colour"][1]) + "\" B=\"" + str(p["colour"][2]) + "\" />")
    
    if p["model"]:
        print("<models>")
        print("<model file=\"" + p["model"] + "\"/>")
        print("</models>")

    if p["moons"]:
        moons = p["moons"]
        for moon in moons:
            printPlaneta(moon, moons[moon], scale)

    print("</group>")

print("<scene>")
for planeta in planetas:
    printPlaneta(planeta, planetas[planeta], 1)
print("</scene>")
