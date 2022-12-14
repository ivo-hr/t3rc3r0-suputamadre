#include "Bomba.h"

Bomba::Bomba(SceneNode* node) : EntidadIG(node)
{
	//La constructora pasa el nodo asociado al objeto creado, como parámetro
	mNode = node;

	mSM = mNode->getCreator();

	mBombaNode = mNode->createChildSceneNode();
	ent = mSM->createEntity("Barrel.mesh");
	ent->setMaterialName("Practica1/chess");
	mBombaNode->attachObject(ent);

	// Animacion desplazamiento
	Animation* animation = mSM->createAnimation("animVV", duration);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mBombaNode);
	Vector3 keyframePos(0.0, 0.0, 0.0); // Posicion del keyframe
	Vector3 src(0.0, 0.0, 1.0); // Rotacion del keyframe
	Real durPaso = duration / 4.0; // 5 keyFrames: origen(0), arriba, origen, abajo, origen(4)

	TransformKeyFrame* kf;

	// Keyframe 0: origen
	kf = track->createNodeKeyFrame(durPaso * 0);
	kf->setTranslate(keyframePos);

	// Keyframe 1: arriba
	kf = track->createNodeKeyFrame(durPaso * 1);
	keyframePos += Vector3::UNIT_Y * distance;
	kf->setTranslate(keyframePos);
	kf->setRotation(src.getRotationTo(Vector3(1.0, 0.0, 1.0)));

	// Keyframe 2: origen
	kf = track->createNodeKeyFrame(durPaso * 2);
	keyframePos += Vector3::NEGATIVE_UNIT_Y * distance;
	kf->setTranslate(keyframePos);

	// Keyframe 3: abajo
	kf = track->createNodeKeyFrame(durPaso * 3);
	keyframePos += Vector3::NEGATIVE_UNIT_Y * distance;
	kf->setTranslate(keyframePos);
	kf->setRotation(src.getRotationTo(Vector3(-1.0, 0.0, 1.0)));

	// Keyframe 4: origen
	kf = track->createNodeKeyFrame(durPaso * 4);
	keyframePos += Vector3::UNIT_Y * distance;
	kf->setTranslate(keyframePos);

	animationState = mSM->createAnimationState("animVV");
	animationState->setEnabled(true);
	animationState->setLoop(true);

	/*pSys = mSM->createParticleSystem("psBomb", "Practica1/bomb");
	pSys->setEmitting(true);
	mPSNode = mBombaNode->createChildSceneNode();
	mPSNode->attachObject(pSys);*/
	
	addListener(this);
}

void Bomba::frameRendered(const FrameEvent& evt) 
{
	if(isMoving)
		animationState->addTime(evt.timeSinceLastFrame);
}

void Bomba::receiveEvent(MessageType msgType, EntidadIG* entidad) 
{
	switch (msgType)
	{
	case msgBomba: 
		isMoving = !isMoving;
		animationState->setEnabled(false);
		break;
	case msgBombaBoom:
		pSys = mSM->createParticleSystem("psBomb", "Practica1/bomb");
		pSys->setEmitting(true);
		mPSNode = mNode->createChildSceneNode();
		mPSNode->attachObject(pSys);
		mBombaNode->setVisible(false);
		break;

	default: 
		break;
	}
}