package nara.zeio.storages;

import java.util.List;
import nara.zeio.beans.Ponto;

import org.springframework.data.repository.PagingAndSortingRepository;
import org.springframework.data.repository.query.Param;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;
import org.springframework.web.bind.annotation.CrossOrigin;


@RepositoryRestResource(collectionResourceRel = "pontos", path = "pontos")

public interface PontoRepository extends PagingAndSortingRepository<Ponto, Long> {
	List<Ponto> findByX(@Param("x") String x);
	List<Ponto> findByXAndYAndRad(@Param("x") double x, @Param("y") double y, @Param("rad") double rad);
}
