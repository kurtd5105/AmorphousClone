#include "Player.h"
#include <GameEngine/Sprite.h>
#include <GameEngine/SpriteInfo.h>
#include <GameEngine/SpriteManager.h>

Player::Player(): _knockback(false), _invincible(false), _step(0.0f), _prevStep(0.0f), _targetRotation(0.0f), _gloopleBumps(0) {}

Player::~Player() {}

void Player::init(GameEngine::SpriteInfo* info, glm::vec2 scalingFactors, std::string slowFx) {
	_x = info->x;
	_y = info->y;
	_width = info->width;
	_height = info->height;
	_depth = info->depth;

	// Assumes player is a circle.
	_radius = _width / 2;
	_speed = PLAYER_SPEED;
	_SpriteManager = info->manager;
	
	// Loads the main sprite into the sprite manager.
	_sprite = _SpriteManager->addSprite(_x, _y, _width, _height, _depth, info->UVmM, info->path);

	// Loads the slowed effect sprite into the sprite manager, at a slightly lower depth so that it is seen over top of the main sprite.
	_slowedEffect = _SpriteManager->addSprite(_x, _y, _width, _height, _depth - 0.1f, info->UVmM, slowFx);
	// Sets the slowed effect to not be seen.
	_slowedEffect->setInvisible();
	// Tracks the subsprite so that it can be translated with the player.
	_subSprites.push_back(_slowedEffect);

	// Initializes the enemy's hitbox, assumed to also be a circle.
	_hitbox.init(_x, _y, _width, _height, _radius, GameEngine::CIRC);

	// Adds the Player's sword subagent.
	_sword.init(_x, _y, _rotation, scalingFactors, _SpriteManager);
	// Tracks the subagent so that it can be translated with the player.
	_subAgents.push_back(&_sword);

	_isInit = true;
}

void Player::onCollide(EnemyType type, float targetRotation) {
	// If the player collided with a Goople then increase the count of collisions with one.
	if(type == GOOPLE) {
		_gloopleBumps++;
	// If the player collided with a stickie then slow the player
	} else if(type == STICKIE) {
		slow();
	}

	// If the player has been bumped 3 times by a Goople then the player dies.
	if(_gloopleBumps >= 3) {
		_alive = false;
	// If the player isn't invincible and isn't currently being knocked back then knock the player back.
	} else if(!_invincible && !_knockback) {
		_knockback = true;
		_invincible = true;
		_targetRotation = targetRotation;
	}
}

void Player::knockback(float step) {
	// Increase the time counter for the knockback effect.
	_prevStep = _step;
	_step += step;

	// If the player hasn't been knocked back long enough
	if(_step <= KNOCKBACK_TIME) {
		// Remove invulnerability after the timer is over.
		if(_step > INVULNERABLE_TIME) {
			_invincible = false;
		}

		// Move the player away from the collision.
		float xMove = cos(_targetRotation) * KNOCKBACK_SPEED * step;
		float yMove = sin(_targetRotation) * KNOCKBACK_SPEED * step;

		_x += xMove;
		_y += yMove;

		// Move the main sprite.
		_sprite->translate(xMove, yMove);
		// Move the slow effect.
		_slowedEffect->translate(xMove, yMove);
		// Move the player's sword, and increase the speed by the slow multiplier as the sword will already automatically be slowed.
		_sword.translate(xMove, yMove, 1.0f / (_isSlowed ? SLOW_MULT : 1.0f));
	} else {
		// Knock back the player the remainder of the distance that the player should be knocked back for.
		if(_prevStep <= KNOCKBACK_TIME) {
			// Move the player away from the collision for the remainder of the knockback time.
			float xMove = cos(_targetRotation) * KNOCKBACK_SPEED * (KNOCKBACK_TIME - _prevStep);
			float yMove = sin(_targetRotation) * KNOCKBACK_SPEED * (KNOCKBACK_TIME - _prevStep);

			_x += xMove;
			_y += yMove;

			// Move the main sprite.
			_sprite->translate(xMove, yMove);
			// Move the slow effect.
			_slowedEffect->translate(xMove, yMove);
			// Move the player's sword, and increase the speed by the slow multiplier as the sword will already automatically be slowed.
			_sword.translate(xMove, yMove, 1.0f / (_isSlowed ? SLOW_MULT : 1.0f));
		}

		// Remove the knockback and invulnerability.
		_knockback = false;
		_invincible = false;

		// Reset the knockback timers.
		_step = _prevStep = 0.0f;
	}
}
