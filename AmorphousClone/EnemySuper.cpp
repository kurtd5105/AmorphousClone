#include "EnemySuper.h"

EnemySuper::EnemySuper(): _chance(0.0f), _collided(false), _hasGoo(false), _goo(nullptr), _Random(nullptr) {}


EnemySuper::~EnemySuper() {}

void EnemySuper::init(float x, float y, float width, float height, float depth, int side, 
					  std::vector<float> UVmM, std::string path, std::string slowFx, GameEngine::SpriteManager* manager, GameEngine::Random* Random) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_depth = depth;

	// Assumption of enemy being a circle.
	_radius = width / 2;

	_speed = ENEMY_SPEED;
	_SpriteManager = manager;

	// Loads the main sprite into the sprite manager.
	_sprite = _SpriteManager->addSprite(x, y, width, height, depth, UVmM, path);

	// Loads the slowed effect sprite into the sprite manager, at a slightly lower depth so that it is seen over top of the main sprite.
	_slowedEffect = _SpriteManager->addSprite(x, y, width, height, depth - 0.1f, UVmM, slowFx);
	// Sets the slowed effect to not be seen.
	_slowedEffect->setInvisible();
	// Tracks the subsprite so that it can be translated with the enemy.
	_subSprites.push_back(_slowedEffect);

	// Initializes the enemy's hitbox, assumed to also be a circle.
	_hitbox.init(x, y, width, height, _radius, GameEngine::CIRC);

	_chance = 0.90f;
	_Random = Random;
	_isInit = true;
	//logicInit(side);
}

void EnemySuper::moveToTarget(float speed) {
	if(_enabled) {
		// If the enemy hasn't reached its target yet.
		if(getPos() != _target) {
			// Get the distance to the target and point at it.
			auto distanceTo = getCentered() - _target;
			_sprite->pointAt(_target);
			_slowedEffect->pointAt(_target);
			auto angle = getRotation();

			float xMove, yMove;

			// Prevent the target from being overshot in the x direction.
			xMove = cos(angle) * _speed * speed * (_isSlowed ? SLOW_MULT : 1.0f);
			if(xMove >= abs(distanceTo.x)) {
				xMove = distanceTo.x;
				_x = _target.x;
			} else {
				_x += xMove;
			}

			// Prevent the target from being overshot in the y direction.
			yMove = sin(angle) * _speed * speed * (_isSlowed ? SLOW_MULT : 1.0f);
			if(yMove >= abs(distanceTo.y)) {
				yMove = distanceTo.y;
				_y = _target.y;
			} else {
				_y += yMove;
			}
			
			// Translate the main sprite and slow effect sprite.
			_sprite->translate(xMove, yMove);
			_slowedEffect->translate(xMove, yMove);
			//this->translate(xMove, yMove, speed);
		// If the target has been reached then the enemy can be removed now.
		} else {
			// Delete both its main sprite and slow sprite from the sprite manager.
			_SpriteManager->deleteSprite(_sprite);
			_SpriteManager->deleteSprite(_slowedEffect);
			_slowedEffect = nullptr;
			_sprite = nullptr;

			// Disable the enemy.
			_enabled = false;
		}
	}
}

void EnemySuper::kill() {
	// Disable the enemy and make it invisible.
	disable();
	setInvisible();

	_alive = false;

	// Kill all subagents belonging to the enemy.
	for(unsigned int i = 0; i < _subAgents.size(); i++) {
		_subAgents[i]->kill();
	}

	// Spawn goo if the enemy has goo.
	if(_hasGoo) {
		// Spawn the new goo as twice as big as the enemy, and center it on the enemy.
		_goo = new StickieGoo(_x - (_width / 2.0f), _y - (_height / 2.0f), _width * 2, _height * 2, 50.0f, std::vector<float>{}, "Textures/StickieGoo.png", _SpriteManager);
	}
}
