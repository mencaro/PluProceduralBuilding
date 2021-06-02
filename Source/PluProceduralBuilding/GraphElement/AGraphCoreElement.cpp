// Fill out your copyright notice in the Description page of Project Settings.


#include "AGraphCoreElement.h"

#include <string>


// Sets default values
AAGraphCoreElement::AAGraphCoreElement()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    ///mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	eachTriangleNormal.Init(FVector(0.0f, 0.0f, 1.0f), 3);
	eachTriangleTangents.Init(FProcMeshTangent(1.0f, 0.0f, 0.0f), 3);
	eachTriangleVertexColors.Init(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f), 3);
	//
	SM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(SM);
}

// Called when the game starts or when spawned
void AAGraphCoreElement::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAGraphCoreElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AAGraphCoreElement::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ClearSearchAndRegisterAllComponentsNodesAndBranch();
	CreateProceduralSections();
}

void AAGraphCoreElement::CreateProceduralSections()
{
	float g1 = 2.79; float g2 = 3.1;
	//ветки
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				if(It.Value().ArrayData[i].bOrientationConnectNode)
				{
					ClearProceduralElements();
					//
					vertices.Push(It.Value().ArrayData[i].PointStart_L);
					vertices.Push(It.Value().ArrayData[i].PointEnd_L);
					vertices.Push(It.Value().ArrayData[i].PointEnd_R);
					vertices.Push(It.Value().ArrayData[i].PointStart_R);
					//Change the name for the next possible item
					FString Str = "MyPMC" + It.Key().ToString() + FString::FromInt(i+1);
					//Convert the FString to FName
					FName InitialName = (*Str);
					UProceduralMeshComponent* NewComp = NewObject<UProceduralMeshComponent>(this, UProceduralMeshComponent::StaticClass(),InitialName);
					NewComp->RegisterComponent();
					NewComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
					NewComp->bUseAsyncCooking = true;
					CreateSection();
					//mesh->ClearAllMeshSections();
					//mesh->ClearNeedEndOfFrameUpdate();
					NewComp->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
					// if (isSideWalkType == true) mesh->SetMaterial(0, Material1);
					// else mesh->SetMaterial(0, Material0);
					NewComp->ContainsPhysicsTriMeshData(true); //Enable collision data
					//mesh->bUseComplexAsSimpleCollision = false;
					//mesh->AddCollisionConvexMesh(vertices);
					NewComp->SetMobility(EComponentMobility::Static);
					NewComp->SetEnableGravity(false);
					ProceduralMeshes.Add(NewComp);
				}
			}
		}
	}
	//узлы
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		ClearProceduralElements();
		if (It.Value().ArrayData.Num()>0)
		{
			if (It.Value().ArrayData.Num() == 2)
			{
				float a = It.Value().ArrayData[0].route_relatively_node.DotProduct(It.Value().ArrayData[0].route_relatively_node,It.Value().ArrayData[1].route_relatively_node);
				a = acos(a);
				UE_LOG(LogTemp, Warning, TEXT("МЕЖДУ ЛИНИЯМИ: %f"), a);
				if ((a > g1) && (a <g2))
				{
					for(int i = 0; i < It.Value().ArrayData.Num(); i++)
					{
						vertices.Push(It.Value().ArrayData[i].PointStart_L);
						vertices.Push(It.Value().ArrayData[i].PointStart_R);
					}
					//Change the name for the next possible item
					FString Str1 = "PMC_C" + It.Key().ToString() + FString::FromInt(1);
					//Convert the FString to FName
					FName InitialName1 = (*Str1);
					UProceduralMeshComponent* NewComp = NewObject<UProceduralMeshComponent>(this, UProceduralMeshComponent::StaticClass(),InitialName1);
					NewComp->RegisterComponent();
					NewComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
					NewComp->bUseAsyncCooking = true;
					CreateSection();
					//mesh->ClearAllMeshSections();
					//mesh->ClearNeedEndOfFrameUpdate();
					NewComp->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
					// if (isSideWalkType == true) mesh->SetMaterial(0, Material1);
					// else mesh->SetMaterial(0, Material0);
					NewComp->ContainsPhysicsTriMeshData(true); //Enable collision data
					//mesh->bUseComplexAsSimpleCollision = false;
					//mesh->AddCollisionConvexMesh(vertices);
					NewComp->SetMobility(EComponentMobility::Static);
					NewComp->SetEnableGravity(false);
					ProceduralMeshes.Add(NewComp);
				}
				else if ((a > g2))
				{
					for(int i = 0; i < It.Value().ArrayData.Num(); i++)
					{
						vertices.Push(It.Value().ArrayData[i].PointStart_L);
						vertices.Push(It.Value().ArrayData[i].PointStart_R);
						if (i == 0)
						{
							vertices.Push(It.Value().ThisMainPosition);
						}
					}
					//Change the name for the next possible item
					FString Str1 = "PMC_C" + It.Key().ToString() + FString::FromInt(1);
					//Convert the FString to FName
					FName InitialName1 = (*Str1);
					UProceduralMeshComponent* NewComp = NewObject<UProceduralMeshComponent>(this, UProceduralMeshComponent::StaticClass(),InitialName1);
					NewComp->RegisterComponent();
					NewComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
					NewComp->bUseAsyncCooking = true;
					CreateSection();
					//mesh->ClearAllMeshSections();
					//mesh->ClearNeedEndOfFrameUpdate();
					NewComp->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
					// if (isSideWalkType == true) mesh->SetMaterial(0, Material1);
					// else mesh->SetMaterial(0, Material0);
					NewComp->ContainsPhysicsTriMeshData(true); //Enable collision data
					//mesh->bUseComplexAsSimpleCollision = false;
					//mesh->AddCollisionConvexMesh(vertices);
					NewComp->SetMobility(EComponentMobility::Static);
					NewComp->SetEnableGravity(false);
					ProceduralMeshes.Add(NewComp);
				}
				else if ((a < g1))
				{
					for(int i = 0; i < It.Value().ArrayData.Num(); i++)
					{
						vertices.Push(It.Value().ArrayData[i].PointStart_L);
						vertices.Push(It.Value().ArrayData[i].PointStart_R);
					}
					vertices.Push(It.Value().ThisMainPosition);
					//Change the name for the next possible item
					FString Str1 = "PMC_C" + It.Key().ToString() + FString::FromInt(1);
					//Convert the FString to FName
					FName InitialName1 = (*Str1);
					UProceduralMeshComponent* NewComp = NewObject<UProceduralMeshComponent>(this, UProceduralMeshComponent::StaticClass(),InitialName1);
					NewComp->RegisterComponent();
					NewComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
					NewComp->bUseAsyncCooking = true;
					CreateSection();
					//mesh->ClearAllMeshSections();
					//mesh->ClearNeedEndOfFrameUpdate();
					NewComp->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
					// if (isSideWalkType == true) mesh->SetMaterial(0, Material1);
					// else mesh->SetMaterial(0, Material0);
					NewComp->ContainsPhysicsTriMeshData(true); //Enable collision data
					//mesh->bUseComplexAsSimpleCollision = false;
					//mesh->AddCollisionConvexMesh(vertices);
					NewComp->SetMobility(EComponentMobility::Static);
					NewComp->SetEnableGravity(false);
					ProceduralMeshes.Add(NewComp);
				}
			}
			else
			{
				for(int i = 0; i < It.Value().ArrayData.Num(); i++)
				{
					vertices.Push(It.Value().ArrayData[i].PointStart_L);
					vertices.Push(It.Value().ArrayData[i].PointStart_R);
				}
				//Change the name for the next possible item
				FString Str1 = "PMC_C" + It.Key().ToString() + FString::FromInt(1);
				//Convert the FString to FName
				FName InitialName1 = (*Str1);
				UProceduralMeshComponent* NewComp = NewObject<UProceduralMeshComponent>(this, UProceduralMeshComponent::StaticClass(),InitialName1);
				NewComp->RegisterComponent();
				NewComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
				NewComp->bUseAsyncCooking = true;
				CreateSection();
				//mesh->ClearAllMeshSections();
				//mesh->ClearNeedEndOfFrameUpdate();
				NewComp->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
				// if (isSideWalkType == true) mesh->SetMaterial(0, Material1);
				// else mesh->SetMaterial(0, Material0);
				NewComp->ContainsPhysicsTriMeshData(true); //Enable collision data
				//mesh->bUseComplexAsSimpleCollision = false;
				//mesh->AddCollisionConvexMesh(vertices);
				NewComp->SetMobility(EComponentMobility::Static);
				NewComp->SetEnableGravity(false);
				ProceduralMeshes.Add(NewComp);
			}
		}
	}
	//крышка
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				if(It.Value().ArrayData[i].bOrientationConnectNode)
				{
					ClearProceduralElements();
					vertices.Push(It.Value().ArrayData[i].PointStart_Lw);
					vertices.Push(It.Value().ArrayData[i].PointEnd_Lw);
					vertices.Push(It.Value().ArrayData[i].PointEnd_Rw);
					vertices.Push(It.Value().ArrayData[i].PointStart_Rw);
					FString Str = "MyPMC_K" + It.Key().ToString() + FString::FromInt(i+1);
					FName InitialName = (*Str);
					UProceduralMeshComponent* NewComp = NewObject<UProceduralMeshComponent>(this, UProceduralMeshComponent::StaticClass(),InitialName);
					NewComp->RegisterComponent();
					NewComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
					NewComp->bUseAsyncCooking = true;
					CreateSection();
					//mesh->ClearAllMeshSections();
					//mesh->ClearNeedEndOfFrameUpdate();
					NewComp->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
					// if (isSideWalkType == true) mesh->SetMaterial(0, Material1);
					// else mesh->SetMaterial(0, Material0);
					NewComp->ContainsPhysicsTriMeshData(true); //Enable collision data
					//mesh->bUseComplexAsSimpleCollision = false;
					//mesh->AddCollisionConvexMesh(vertices);
					NewComp->SetMobility(EComponentMobility::Static);
					NewComp->SetEnableGravity(false);
					ProceduralMeshes.Add(NewComp);
				}
			}
		}
	}
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				ClearProceduralElements();
				if(It.Value().ArrayData[i].bOrientationConnectNode)
				{
					FVector a_vec = It.Value().ArrayData[i].PointStart_Rw - It.Value().ArrayData[i].PointStart_R;
					FVector b_vec = It.Value().ArrayData[i].PointEnd_R - It.Value().ArrayData[i].PointStart_R;
					FVector n_vec;
					n_vec = n_vec.CrossProduct(a_vec,b_vec);
					nTriangleNormal.Empty();
					nTriangleNormal.Init(n_vec, 3);
					pTriangleTangents.Empty();
					pTriangleTangents.Init(FProcMeshTangent(1.0f, 0.0f, 0.0f), 3);
					vertices.Push(It.Value().ArrayData[i].PointStart_Rw);
					vertices.Push(It.Value().ArrayData[i].PointEnd_Rw);
					vertices.Push(It.Value().ArrayData[i].PointEnd_R);
					vertices.Push(It.Value().ArrayData[i].PointStart_R);
					//Change the name for the next possible item
					FString Str = "MyPMC_kr" + It.Key().ToString() + FString::FromInt(i+1);
					//Convert the FString to FName
					FName InitialName = (*Str);
					UProceduralMeshComponent* NewComp = NewObject<UProceduralMeshComponent>(this, UProceduralMeshComponent::StaticClass(),InitialName);
					NewComp->RegisterComponent();
					NewComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
					NewComp->bUseAsyncCooking = true;
					CreateSection(nTriangleNormal,pTriangleTangents);
					//mesh->ClearAllMeshSections();
					//mesh->ClearNeedEndOfFrameUpdate();
					NewComp->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
					// if (isSideWalkType == true) mesh->SetMaterial(0, Material1);
					// else mesh->SetMaterial(0, Material0);
					NewComp->ContainsPhysicsTriMeshData(true); //Enable collision data
					//mesh->bUseComplexAsSimpleCollision = false;
					//mesh->AddCollisionConvexMesh(vertices);
					NewComp->SetMobility(EComponentMobility::Static);
					NewComp->SetEnableGravity(false);
					ProceduralMeshes.Add(NewComp);
				}
			}
		}
	}
}

void AAGraphCoreElement::PostInitializeComponents()
{
	AActor::PostInitializeComponents();
}

void AAGraphCoreElement::PostActorCreated()
{
	AActor::PostActorCreated();
}

void AAGraphCoreElement::PostLoad()
{
	AActor::PostLoad();
	vertices.Empty();
	Triangles.Empty();
	UV0.Empty();
	normals.Empty();
	vertexColors.Empty();
	tangents.Empty();
}

void AAGraphCoreElement::AddVertexFloor()
{
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				if(It.Value().ArrayData[i].bOrientationConnectNode)
				{
					//vertices.Push(It.Value().ArrayData[i].PointStart);
					vertices.Push(It.Value().ArrayData[i].PointStart_L);
					vertices.Push(It.Value().ArrayData[i].PointEnd_L);
					vertices.Push(It.Value().ArrayData[i].PointEnd);
					vertices.Push(It.Value().ArrayData[i].PointEnd_R);
					vertices.Push(It.Value().ArrayData[i].PointStart_R);
				}
			}
		}
	}
}

void AAGraphCoreElement::GraphRebuildNodeSpace()
{
	UE_LOG(LogTemp, Warning, TEXT("ДЕЛАЕМ ЛИНИИ МЕЖДУ ЛИНИЯМИ: %d"), 0);
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("СЧИТАЕМ УГЛЫ=: %d"), i);
				{
					It.Value().ArrayData[i].angle_route = atan2(It.Value().ArrayData[i].route_relatively_node.X , It.Value().ArrayData[i].route_relatively_node.Y);
				}
			}
		}
	}
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				FConnectionType ct = It.Value().ArrayData[i];
				for(int j = i+1; j < It.Value().ArrayData.Num(); j++)
				{
					if(ct.angle_route > It.Value().ArrayData[j].angle_route)
					{
						FConnectionType ct1 = It.Value().ArrayData[j];
						It.Value().ArrayData[j] = ct;
						It.Value().ArrayData[i] = ct1;
						ct = ct1;
					}
				}
			}
		}
	}
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("The УГОЛ: %f"), It.Value().ArrayData[i].angle_route);
			}
		}
	}
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				//center
				AddLineToBranch
                (
                    "SC_CenterNode_" + It.Key().ToString() + FString::FromInt(i+1),
                    It.Value().ThisMainPosition,
                    It.Value().ArrayData[i].PointStart,//It.Value().ThisMainPosition + It.Value().ArrayData[i].route_relatively_node * It.Value().RangeOuts,
                    It.Value().ArrayData[i].route_relatively_node
                );
				// //right
				AddLineToBranch
                (
                    "SC_CenterNodeRight_" + It.Key().ToString() + FString::FromInt(i+1),
                    It.Value().ThisMainPosition,
                    It.Value().ArrayData[i].PointStart_R,
                    It.Value().ArrayData[i].route_relatively_node
                );
				//left
				AddLineToBranch
                (
                    "SC_CenterNodeLeft_" + It.Key().ToString() + FString::FromInt(i+1),
                    It.Value().ThisMainPosition,
                    It.Value().ArrayData[i].PointStart_L,
                    It.Value().ArrayData[i].route_relatively_node
                );
				
				int k = i + 1;
				if(i == It.Value().ArrayData.Num()-1) {k = 0;}
    
				AddLineToBranch
                (
                    "SC_RightLeftNode_" + It.Key().ToString() + FString::FromInt(i+1),
                    It.Value().ArrayData[i].PointStart_R,
                    It.Value().ArrayData[k].PointStart_L,
                    It.Value().ArrayData[i].route_relatively_node
                );
			}
		}
	}
}

void AAGraphCoreElement::CreateSection()
{
	TArray<float> vertexXCoordinates;
	vertexXCoordinates.Empty();
	TArray<float> vertexYCoordinates;
	vertexYCoordinates.Empty();
	polygonVertices.clear();
	polygon.clear();
	for (int i = 0; i < vertices.Num(); i++)
	{
		Point vertex;
		vertex[0] = vertices[i].X;
		vertex[1] = vertices[i].Y; 
		vertexXCoordinates.Add(vertices[i].X);
		vertexYCoordinates.Add(vertices[i].Y);
		polygonVertices.push_back(vertex);
	}
	polygon.push_back(polygonVertices);
	std::vector<N> indices = mapbox::earcut<N>(polygon);
	//3 consecutive indices in clockwise order of the vertices of the input polygon.

	int i = 0;
	//creating triangles from these indices. Each iteration is a new triangle.
	while ((i + 3) <= indices.size())
	{
		Triangles.Add((uint32_t)indices[i+2]); //assuming that the first triangle starts from 0
		Triangles.Add((uint32_t)indices[i+1]);
		Triangles.Add((uint32_t)indices[i]);
		// Triangles.Add((uint32_t)indices[i]); //assuming that the first triangle starts from 0
		// Triangles.Add((uint32_t)indices[i+1]);
		// Triangles.Add((uint32_t)indices[i+2]);
		normals.Append(eachTriangleNormal);
		tangents.Append(eachTriangleTangents);
		vertexColors.Append(eachTriangleVertexColors);
		i += 3;
	}
		/*
	UV mapping calculation - We need to map the 2D texture surface to the 2D junction surface.
	We need to find the Xmax, Xmin, Ymax and Ymin of the polygon. Then we calculate Xrange and Yrange of the polygon.
	After normalizing the coordinates of the vertices over this range, we can make the polygon fit over the 2D texture.
	*/
	float Xrange = FMath::Max(vertexXCoordinates) - FMath::Min(vertexXCoordinates);
	float Yrange = FMath::Max(vertexYCoordinates) - FMath::Min(vertexYCoordinates);	
	float minimumX = FMath::Min(vertexXCoordinates);
	float minimumY = FMath::Min(vertexYCoordinates);
	for (int32 i1 = 0; i1 < vertices.Num(); i1++) {
		float X = (vertices[i1].X - minimumX) / 50.0f;
		float Y = (vertices[i1].Y - minimumY) / 50.0f;
		UE_LOG(LogEngine, Warning, TEXT("-=-=-=-=-=-=-=-= NORMALIZED VERTEX X COORDINATE IS %d -=-=-=-="), X);
		UE_LOG(LogEngine, Warning, TEXT("-=-=-=-=-=-=-=-= NORMALIZED VERTEX Y COORDINATE IS %d -=-=-=-="), Y);
		UV0.Add(FVector2D(X, Y));
	}
	vertexXCoordinates.Empty();
	vertexYCoordinates.Empty();
}

void AAGraphCoreElement::CreateSection(TArray<FVector> nTN, TArray<FProcMeshTangent> pTT)
{
	TArray<float> vertexXCoordinates;
	vertexXCoordinates.Empty();
	TArray<float> vertexYCoordinates;
	vertexYCoordinates.Empty();
	polygonVertices.clear();
	polygon.clear();
	for (int i = 0; i < vertices.Num(); i++)
	{
		Point vertex;
		vertex[0] = vertices[i].X;
		vertex[1] = vertices[i].Y; 
		vertexXCoordinates.Add(vertices[i].X);
		vertexYCoordinates.Add(vertices[i].Y);
		polygonVertices.push_back(vertex);
	}
	polygon.push_back(polygonVertices);
	std::vector<N> indices = mapbox::earcut<N>(polygon);
	//3 consecutive indices in clockwise order of the vertices of the input polygon.

	int i = 0;
	//creating triangles from these indices. Each iteration is a new triangle.
	while ((i + 3) <= indices.size())
	{
		Triangles.Add((uint32_t)indices[i+2]); //assuming that the first triangle starts from 0
		Triangles.Add((uint32_t)indices[i+1]);
		Triangles.Add((uint32_t)indices[i]);
		// Triangles.Add((uint32_t)indices[i]); //assuming that the first triangle starts from 0
		// Triangles.Add((uint32_t)indices[i+1]);
		// Triangles.Add((uint32_t)indices[i+2]);
		normals.Append(nTN);
		tangents.Append(pTT);
		vertexColors.Append(eachTriangleVertexColors);
		i += 3;
	}
		/*
	UV mapping calculation - We need to map the 2D texture surface to the 2D junction surface.
	We need to find the Xmax, Xmin, Ymax and Ymin of the polygon. Then we calculate Xrange and Yrange of the polygon.
	After normalizing the coordinates of the vertices over this range, we can make the polygon fit over the 2D texture.
	*/
	float Xrange = FMath::Max(vertexXCoordinates) - FMath::Min(vertexXCoordinates);
	float Yrange = FMath::Max(vertexYCoordinates) - FMath::Min(vertexYCoordinates);	
	float minimumX = FMath::Min(vertexXCoordinates);
	float minimumY = FMath::Min(vertexYCoordinates);
	for (int32 i1 = 0; i1 < vertices.Num(); i1++) {
		float X = (vertices[i1].X - minimumX) / 50.0f;
		float Y = (vertices[i1].Y - minimumY) / 50.0f;
		UE_LOG(LogEngine, Warning, TEXT("-=-=-=-=-=-=-=-= NORMALIZED VERTEX X COORDINATE IS %d -=-=-=-="), X);
		UE_LOG(LogEngine, Warning, TEXT("-=-=-=-=-=-=-=-= NORMALIZED VERTEX Y COORDINATE IS %d -=-=-=-="), Y);
		UV0.Add(FVector2D(X, Y));
	}
	vertexXCoordinates.Empty();
	vertexYCoordinates.Empty();
}
void AAGraphCoreElement::ClearAllBuilding()
{
	for (auto It = StaticMeshes.CreateIterator(); It; It++)
	{
		(*It)->DestroyComponent();
	}
	for (auto It = SplineComponents.CreateIterator(); It; It++)
	{
		(*It)->DestroyComponent();
	}
	for (auto It = ProceduralMeshes.CreateIterator(); It; It++)
	{
		(*It)->DestroyComponent();
	}
	StaticMeshes.Empty();
	SplineComponents.Empty();
	ProceduralMeshes.Empty();
	TNodes.Empty();
}

void AAGraphCoreElement::ClearProceduralElements()
{
	//
	vertices.Empty();
	Triangles.Empty();
	UV0.Empty();
	normals.Empty();
	vertexColors.Empty();
	tangents.Empty();
	//
}

void AAGraphCoreElement::ClearSearchAndRegisterAllComponentsNodesAndBranch()
{
	ClearAllBuilding();
	RegisterAllComponents();//Register all the components
	SearchNodesInTheWorld();
	SearchBranches();
	GraphRebuildNodeSpace();
}
void AAGraphCoreElement::GetAllActorsLevel(TSubclassOf<UInterface> myInterfase, TArray<AActor*> &foundEnemies)
{
	GLog->Log("GetAllActorsLevel");
	//TSubclassOf<AActor> classToFind;
	//classToFind = AA_Graph_Node_Base::StaticClass();
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, foundEnemies);
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), myInterfase, foundEnemies);
	UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), foundEnemies.Num());
}
void AAGraphCoreElement::SearchNodesInTheWorld()
{
	GetAllActorsLevel(UI_NodeGraph::StaticClass(),TNodes);
}
void AAGraphCoreElement::SearchBranches()
{
	DataConnectNode.Empty();
	UE_LOG(LogTemp, Warning, TEXT("СОБИРАЕМ УЗЛЫ: %d"), 0);
	for(int i = 0; i < TNodes.Num(); i++)
	{
		FGuid g = II_GraphAction::Execute_IGetGUID(TNodes[i]);
		DataConnectNode.Add(g,II_GraphAction::Execute_IGetConnectionNode(TNodes[i]));
	}
	UE_LOG(LogTemp, Warning, TEXT("СОБИРАЕМ ОБРАТНЫЕ ВЕТВИ: %d"), 0);
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		UE_LOG(LogTemp, Warning, TEXT("DataConnectNode.CreateIterator(): %d"), 0);
		UE_LOG(LogTemp, Warning, TEXT("It.Value().ArrayData.Num(): %d"), It.Value().ArrayData.Num());
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("It.Value().ArrayData.Num().i: %d"), i);
				if(It.Value().ArrayData[i].bOrientationConnectNode)
				{
					FConnectionType c = It.Value().ArrayData[i];
					c.bOrientationConnectNode = false;
					c.aConnectionNode = It.Value().pointOnThis;
					if(DataConnectNode.Contains(II_GraphAction::Execute_IGetGUID(It.Value().ArrayData[i].aConnectionNode)))
						DataConnectNode[II_GraphAction::Execute_IGetGUID(It.Value().ArrayData[i].aConnectionNode)].ArrayData.Add(c);
					UE_LOG(LogTemp, Warning, TEXT("ОБРАТ: %d"), i);
				}
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("ОБСЧЕТ: %d"), 0);
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				if(It.Value().ArrayData[i].aConnectionNode != nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("ОБСЧЕТ=: %d"), i);
					It.Value().ArrayData[i].route_relatively_node =
						UBFL_MathGraph::FindRouteVectorBranch
						(
							It.Value().ThisMainPosition,
							It.Value().ArrayData[i].aConnectionNode->GetActorLocation()
						);
					It.Value().ArrayData[i].route_relatively_node.Normalize();
					It.Value().ArrayData[i].routeBranchNorm =
						It.Value().ArrayData[i].route_relatively_node.CrossProduct(It.Value().ArrayData[i].route_relatively_node, FVector(0,0,1));
					//
					{
						It.Value().ArrayData[i].PointStart =
							It.Value().ThisMainPosition +
								It.Value().ArrayData[i].route_relatively_node * It.Value().RangeOuts;
						//
						It.Value().ArrayData[i].PointEnd =
							 It.Value().ArrayData[i].aConnectionNode->GetActorLocation() +
								(It.Value().ArrayData[i].route_relatively_node * (-1)) * It.Value().RangeOuts;
						//
						It.Value().ArrayData[i].PointStart_R =
							It.Value().ArrayData[i].PointStart + It.Value().ArrayData[i].routeBranchNorm * It.Value().ArrayData[i].wightBranch;
						It.Value().ArrayData[i].PointEnd_R =
                            It.Value().ArrayData[i].PointEnd + It.Value().ArrayData[i].routeBranchNorm * It.Value().ArrayData[i].wightBranch;
						It.Value().ArrayData[i].PointStart_L =
                            It.Value().ArrayData[i].PointStart + It.Value().ArrayData[i].routeBranchNorm * (-1) * It.Value().ArrayData[i].wightBranch;
						It.Value().ArrayData[i].PointEnd_L =
                            It.Value().ArrayData[i].PointEnd + It.Value().ArrayData[i].routeBranchNorm * (-1) * It.Value().ArrayData[i].wightBranch;
						//
						It.Value().ArrayData[i].PointStart_Rw =It.Value().ArrayData[i].PointStart_R;
						It.Value().ArrayData[i].PointStart_Rw.Z =It.Value().ArrayData[i].PointStart_R.Z + 150;
						It.Value().ArrayData[i].PointEnd_Rw = It.Value().ArrayData[i].PointEnd_R;
						It.Value().ArrayData[i].PointEnd_Rw.Z = It.Value().ArrayData[i].PointEnd_R.Z + 150;
						It.Value().ArrayData[i].PointStart_Lw = It.Value().ArrayData[i].PointStart_L;
						It.Value().ArrayData[i].PointStart_Lw.Z = It.Value().ArrayData[i].PointStart_L.Z + 150;
						It.Value().ArrayData[i].PointEnd_Lw = It.Value().ArrayData[i].PointEnd_L;
						It.Value().ArrayData[i].PointEnd_Lw.Z = It.Value().ArrayData[i].PointEnd_L.Z + 150;
					}
				}
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("ДЕЛАЕМ ЛИНИИ: %d"), 0);
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("ДЕЛАЕМ ЛИНИИ=: %d"), i);
				if(It.Value().ArrayData[i].bOrientationConnectNode)
				{
					AddLineToBranch
					(
						"SC_Center_" + It.Key().ToString() + FString::FromInt(i+1),
						It.Value().ArrayData[i].PointStart,
						It.Value().ArrayData[i].PointEnd,
						It.Value().ArrayData[i].route_relatively_node
					);
					AddLineToBranch
                    (
                        "SC_Right_" + It.Key().ToString() + FString::FromInt(i+1),
                        It.Value().ArrayData[i].PointStart_R,
                        It.Value().ArrayData[i].PointEnd_R,
                        It.Value().ArrayData[i].route_relatively_node
                    );
					AddLineToBranch
                    (
                        "SC_Left_" + It.Key().ToString() + FString::FromInt(i+1),
                        It.Value().ArrayData[i].PointStart_L,
                        It.Value().ArrayData[i].PointEnd_L,
                        It.Value().ArrayData[i].route_relatively_node
                    );
					AddLineToBranch
					(
						"SC_Right_w" + It.Key().ToString() + FString::FromInt(i+1),
						It.Value().ArrayData[i].PointStart_Rw,
						It.Value().ArrayData[i].PointEnd_Rw,
						It.Value().ArrayData[i].route_relatively_node
					);
					AddLineToBranch
					(
						"SC_Left_w" + It.Key().ToString() + FString::FromInt(i+1),
						It.Value().ArrayData[i].PointStart_Lw,
						It.Value().ArrayData[i].PointEnd_Lw,
						It.Value().ArrayData[i].route_relatively_node
					);
				}
			}
		}
	}
}
void AAGraphCoreElement::IGraphRebuildNodeSpace_Implementation()
{
	GraphRebuildNodeSpace();
}

void AAGraphCoreElement::AddLineToBranch(FString NameComponent, FVector Start, FVector End, FVector RouteBranch)
{
	FName InitialName = (*NameComponent);
	USplineComponent* SC = NewObject<USplineComponent>(this, USplineComponent::StaticClass(), InitialName);
	SC->RegisterComponent();
	AddStartEndDataToBranch(SC,Start,End,RouteBranch);
	SplineComponents.Add(SC);
}
void AAGraphCoreElement::AddStartEndDataToBranch(USplineComponent* Spline_, FVector Start, FVector End, FVector RouteBranch)
{
	GLog->Log("AddStartEndDataToBranch");
	Spline_->SetLocationAtSplinePoint(0,Start,ESplineCoordinateSpace::Type::World);
	Spline_->SetTangentAtSplinePoint(0,RouteBranch,ESplineCoordinateSpace::Type::World);
	Spline_->SetLocationAtSplinePoint(1,End,ESplineCoordinateSpace::Type::World);
	Spline_->SetTangentAtSplinePoint(1,RouteBranch,ESplineCoordinateSpace::Type::World);
}



//for (int32 i = 0; i < 20; i++)
//{
	////Change the name for the next possible item
	//FString Str = "MyCompName" + FString::FromInt(i+1);
	////Convert the FString to FName
	//InitialName = (*Str);
	//UStaticMeshComponent* NewComp = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(),InitialName);
	//NewComp->RegisterComponent();
	//NewComp->SetStaticMesh(SM->GetStaticMesh());
	////Set a random location based on the values we enter through the editor
	//FVector Location;
	////Set the random seed in case we need to change our random values
	//FMath::SRandInit(5);
	//Location.X += FMath::RandRange(-FMath::Abs(3), FMath::Abs(3));
	//Location.Y += FMath::RandRange(-FMath::Abs(4), FMath::Abs(4));
	//NewComp->SetWorldLocation(Location);
	//NewSpline->RegisterComponentWithWorld(GetWorld());
	//NewComp->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
	//StaticMeshes.Add(NewComp);
//}
//