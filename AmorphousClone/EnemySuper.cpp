#include "EnemySuper.h"
#include "StickieGoo.h"
#include <GameEngine/Random.h>
#include <GameEngine/Sprite.h>
#include <GameEngine/SpriteInfo.h>
#include <GameEngine/SpriteManager.h>

#include <memory>

EnemySuper::EnemySuper(): _chance(0.0f), _collided(false), _hasGoo(false), _goo(nullptr), _Random(nullptr) {}

EnemySuper::~EnemySuper() {}

void EnemySuper::init(GameEngine::SpriteInfo* info, int side, std::string slowFx, GameEngine::Random* Random) {
	_x = info->x;
	_y = info->y;
	_width = info->width;
	_height = info->height;
	_depth = info->depth;

	// Assumption of enemy being a circle.
	_radius = info->width / 2;

	_speed = ENEMY_SPEED;
	_SpriteManager = info->manager;

	// Loads the main sprite into the sprite manager.
	_sprite = _SpriteManager->addSprite(_x, _y, _width, _height, _depth, info->UVmM, info->path);

	// Loads the slowed effect sprite into the sprite manager, at a slightly lower depth so that it is seen over top of the main sprite.
	_slowedEffect = _SpriteManager->addSprite(_x, _y, _width, _height, _depth - 0.1f, info->UVmM, slowFx);
	// Sets the slowed effect to not be seen.
	_slowedEffect->setInvisible();
	// Tracks the subsprite so that it can be translated with the enemy.
	_subSprites.push_back(_slowedEffect);

	// Initializes the enemy's hitbox, assumed to also be a circle.
	_hitbox.init(_x, _y, _width, _height, _radius, GameEngine::CIRC);

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
		std::unique_ptr<GameEngine::SpriteInfo> info = std::make_unique<GameEngine::SpriteInfo>(_x - (_width / 2.0f), _y - (_height / 2.0f),
			_width * 2, _height * 2, 50.0f, std::vector<float>{}, "Textures/StickieGoo.png", _SpriteManager);
		_goo = new StickieGoo(info.get());
	}
}
